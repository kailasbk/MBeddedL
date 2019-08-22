#ifndef _MBDL_DRIVE_H_
#define _MBDL_DRIVE_H_

#include "main.h"

namespace mbdl::drive {
extern devices::Out* left;
extern devices::Out* right;
extern devices::In* encoders[3];
extern double width;
extern double theta;

void tracking(void* params);
void create(double w, devices::Out* l, devices::Out* r, devices::In* enc[3]);

void tank(double left, double right);
void arcade(double pwr, double turn);

void turn(double goal);
void to(math::Vector goal);

extern math::Vector position;
extern math::Vector displacement;
extern math::Vector heading;
extern math::Matrix transformation;
}

#endif