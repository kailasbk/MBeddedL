#include "mbdl/motion.h"

static void strafeTurnLoop(void* params)
{
    okapi::Rate timer;
    while (true) {
        strafe.moveVelocity((right.getTargetVelocity() - left.getTargetVelocity()) / 2);
        timer.delayUntil(5_ms);
    }
}

static pros::Task strafeTask(strafeTurnLoop);

void strafeOn()
{
    strafeTask.resume();
}

void strafeOff()
{
    strafeTask.suspend();
}

void turntoAngle(okapi::QAngle angle, bool change)
{
    if (change) {
        strafeTask.resume();
    }
    driveController->turnToAngle(angle);
    if (change) {
        strafeTask.suspend();
    }
}

void driveToPoint(okapi::Point point, bool change)
{
    if (change) {
        strafeTask.resume();
    }
    driveController->driveToPoint(point);
    if (change) {
        strafeTask.suspend();
    }
}