#pragma once

#include "mbdl/config.h"

void strafeOn();
void strafeOff();

void turnToAngle(okapi::QAngle angle, bool change = false);
void driveToPoint(okapi::Point point, bool change = false);