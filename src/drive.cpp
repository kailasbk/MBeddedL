#include "mbdl/drive.h"

namespace mbdl::drive {
math::Vector<2> position;
math::Vector<2> displacement;
math::Vector<2> heading;
double theta = 0;

devices::Out* left = nullptr;
devices::Out* right = nullptr;
devices::In* encoders[3]{ nullptr, nullptr, nullptr };
double width = 0;

math::Matrix<2, 2> transformation;

void create(double w, devices::Out* l, devices::Out* r, devices::In* enc[3])
{
    left = l;
    right = r;
    for (int i = 0; i < 3; i++) {
        encoders[i] = enc[i];
    }
    width = w;
    pros::Task tracking(controlTask);
}

double* buffer = new double[64];
pros::Mutex command;

void controlTask(void* params)
{
    buffer[0] = TANK;
    std::uint32_t timing = pros::millis(), elapsed = 0;
    double slewPower = 0;
    double dL = 0, dR = 0, dS = 0, L = 0, R = 0, S = 0, dTheta = 0;
    double prevL = 0, prevR = 0, powerL = 0, powerR = 0;
    while (true) {
        command.take(TIMEOUT_MAX); // wait for/take mutex
        /**** TRACKING CODE ****/
        {
            // calculates distance traveled in last cycle
            if (encoders[0] != nullptr) {
                dL = encoders[0]->get() - L;
            }
            if (encoders[1] != nullptr) {
                dR = encoders[1]->get() - R;
            }
            if (encoders[2] != nullptr) {
                dS = encoders[2]->get() - S;
            }

            // update absolute counts
            L += dL;
            R += dR;
            S += dS;

            // calculate anglular change
            dTheta = ((R - L) / width) - theta;

            // update absolute angle
            theta += dTheta;

            // update heading vector for average heading
            heading[0] = cos(theta - (dTheta / 2));
            heading[1] = sin(theta - (dTheta / 2));

            // update transformation vector with heading vector
            transformation[0][0] = heading[0];
            transformation[1][0] = heading[1];
            transformation[0][1] = -heading[1];
            transformation[1][1] = heading[0];

            // calculate displacement during last cycle
            displacement[0] = (dR + dL) / 2;
            displacement[1] = dS;

            // update position with translated displacement
            position = position + (transformation * displacement);

            // update heading to reflect current heading
            heading[0] = cos(theta);
            heading[1] = sin(theta);
        }
        /**** MOTION CODE ****/
        {
            // determine time since last run (for slew rate and motion profiling)
            elapsed = pros::millis() - timing;
            timing += elapsed;

            /**** DETERMINATION OF DRIVE POWER ****/
            if (buffer[0] == TANK) {
                powerL = buffer[1];
                powerR = buffer[2];
            } else if (buffer[0] == ARCADE) {
                powerL = buffer[1] - buffer[2];
                powerR = buffer[1] + buffer[2];
            }

            if (left != nullptr)
                left->set(powerL);
            if (right != nullptr)
                right->set(powerR);
        }
        command.give(); // release mutex
        pros::delay(10);
    }
}

void tank(double l, double r)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = TANK;
    buffer[1] = l;
    buffer[2] = r;
    command.give(); // release mutex
}

void arcade(double pwr, double turn)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = ARCADE;
    buffer[1] = pwr;
    buffer[2] = turn;
    command.give(); // release mutex
}

bool isSettled()
{
    if (0) { // if some condition (not determined)
        return true;
    }
    return false;
}
}