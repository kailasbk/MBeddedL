#include "main.h"

// initialize all 2d vectors
mbdl::math::Vector mbdl::drive::position(2);
mbdl::math::Vector mbdl::drive::displacement(2);
mbdl::math::Vector mbdl::drive::heading(2);
double mbdl::drive::theta = 0;

mbdl::devices::Out* mbdl::drive::left;
mbdl::devices::Out* mbdl::drive::right;
mbdl::devices::In* mbdl::drive::encoders[3];
double mbdl::drive::width;

// initialize 2x2 transformation matrix
mbdl::math::Matrix mbdl::drive::transformation(2, 2);

void mbdl::drive::create(double w, devices::Out* l, devices::Out* r, devices::In* enc[3])
{
    left = l;
    right = r;
    for (int i = 0; i < 3; i++) {
        encoders[i] = enc[i];
    }
    width = w;
    pros::Task tracking(mbdl::drive::tracking);
}

void mbdl::drive::tracking(void* params)
{
    double dL = 0, dR = 0, dS = 0, L = 0, R = 0, S = 0, dTheta = 0;
    while (true) {

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
}

void mbdl::drive::to(mbdl::math::Vector goal)
{
}
