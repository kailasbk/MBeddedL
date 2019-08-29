#include "mbdl/drive.h"

mbdl::math::Vector mbdl::drive::position(2);
mbdl::math::Vector mbdl::drive::displacement(2);
mbdl::math::Vector mbdl::drive::heading(2);
double mbdl::drive::theta = 0;

mbdl::devices::Out* mbdl::drive::left;
mbdl::devices::Out* mbdl::drive::right;
mbdl::devices::In* mbdl::drive::encoders[3];
double mbdl::drive::width;

mbdl::math::Matrix mbdl::drive::transformation(2, 2);

void mbdl::drive::create(double w, devices::Out* l, devices::Out* r, devices::In* enc[3])
{
    left = l;
    right = r;
    for (int i = 0; i < 3; i++) {
        encoders[i] = enc[i];
    }
    width = w;
    pros::Task tracking(mbdl::drive::controlTask);
}

char* mbdl::drive::buffer = new char[64];
pros::Mutex mbdl::drive::command;

void mbdl::drive::controlTask(void* params)
{
    buffer[0] = TANK;
    double dL = 0, dR = 0, dS = 0, L = 0, R = 0, S = 0, dTheta = 0;
    double prevL = 0, prevR = 0, powerL = 0, powerR = 0;
    while (true) {
        command.take(TIMEOUT_MAX); // wait for/take mutex
        /**** TRACKING CODE ****/
        {
            // calculates distance traveled in last cycle
            dL = encoders[0]->get() - L;
            dR = encoders[1]->get() - R;
            dS = encoders[2]->get() - S;

            // update absolute counts
            L += dL;
            R += dR;
            S += dS;

            // calculate anglular change
            dTheta = ((R - L) / width) - theta;

            // update absolute angle
            theta += dTheta;

            // update heading vector
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
        }
        /**** MOTION CODE ****/
        {
            /**** DETERMINATION OF DRIVE POWER ****/
            if (buffer[0] > ARCADE) {
                // determine the value of powerL and powerR based on mode
            } else if (buffer[0] == TANK) {
                powerL = buffer[1];
                powerR = buffer[2];
            } else if (buffer[0] == ARCADE) {
                powerL = buffer[1] - buffer[2];
                powerR = buffer[1] + buffer[2];
            }

            /**** SLEW RATE CONTROL OF DRIVE ****/
            if (powerL - prevL > .005) { // TODO: detemine slew value
                left->set(prevL + .005);
                prevL = prevL + .005;
            } else if (powerL - prevL < -.005) {
                left->set(prevL - .005);
                prevL = prevL - .005;
            } else {
                left->set(powerL);
                prevL = powerL;
            }

            if (powerR - prevR > .005) { // TODO: detemine slew value
                right->set(prevR + .005);
                prevR = prevR + .005;
            } else if (powerR - prevR < -.005) {
                right->set(prevR - .005);
                prevR = prevR - .005;
            } else {
                right->set(powerR);
                prevR = powerR;
            }
        }
        command.give(); // release mutex
        pros::delay(10);
    }
}

void mbdl::drive::tank(double l, double r)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = TANK;
    buffer[1] = l;
    buffer[2] = r;
    command.give(); // release mutex
}

void mbdl::drive::arcade(double pwr, double turn)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = ARCADE;
    buffer[1] = pwr;
    buffer[2] = turn;
    command.give(); // release mutex
}

void mbdl::drive::turn(double goal)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = TURN;
    buffer[1] = goal;
    command.give(); // release mutex
}

void mbdl::drive::arc(double angle, double radius)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = ARC;
    buffer[1] = angle;
    buffer[1 + sizeof(double)] = radius;
    command.give(); // release mutex
}

void mbdl::drive::line(double distance)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = LINE;
    buffer[1] = distance;
    command.give(); // release mutex
}

void mbdl::drive::to(mbdl::math::Vector goal)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = TO;
    *(mbdl::math::Vector*)(buffer + 1) = goal;
    command.give(); // release mutex
}

bool mbdl::drive::isSettled()
{
    if (0) { // if some condition (not determined)
        return true;
    }
    return false;
}