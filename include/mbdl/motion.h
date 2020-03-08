#pragma once

#include "mbdl/config.h"

void strafeOn();
void strafeOff();

void turnToAngle(okapi::QAngle angle);
void driveToPoint(okapi::Point point, bool backwards = false);