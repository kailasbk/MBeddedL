#include "mbdl/motion.h"

static void strafeTurnLoop(void* params)
{
    okapi::Rate timer;
    while (true) {
        strafe.moveVelocity((right.getTargetVelocity() - left.getTargetVelocity()) / 2);
        timer.delay(100_Hz);
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
    strafe.moveVoltage(0);
}

void turntoAngle(okapi::QAngle angle)
{
    driveController->turnToAngle(angle);
}

void driveToPoint(okapi::Point point, bool backwards)
{
    driveController->driveToPoint(point, backwards);
}