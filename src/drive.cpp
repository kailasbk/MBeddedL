#include "main.h"

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

uint8_t mbdl::drive::mode = MANUAL;
char* mbdl::drive::buffer = new char[64];
pros::Mutex mbdl::drive::command;

void mbdl::drive::controlTask(void* params)
{
    double dL = 0, dR = 0, dS = 0, L = 0, R = 0, S = 0, dTheta = 0;
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
            if (mode == AUTO) {
                // TODO: implement this code
            }
            // do nothing if in manual mode
        }
        command.give(); // release mutex
        pros::delay(10);
    }
}

void mbdl::drive::tank(double l, double r)
{
    left->set(l);
    right->set(r);
}

void mbdl::drive::arcade(double pwr, double turn)
{
    left->set(pwr - turn);
    right->set(pwr + turn);
}

void mbdl::drive::turn(double goal)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = _TURN_;
    buffer[1] = goal;
    command.give(); // release mutex
}

void mbdl::drive::arc(double angle, double radius)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = _ARC_;
    buffer[1] = angle;
    buffer[1 + sizeof(double)] = radius;
    command.give(); // release mutex
}

void mbdl::drive::line(double distance)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = _LINE_;
    buffer[1] = distance;
    command.give(); // release mutex
}

void mbdl::drive::to(mbdl::math::Vector goal)
{
    command.take(TIMEOUT_MAX); // wait for/take mutex
    buffer[0] = _TO_;
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