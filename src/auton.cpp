#include "mbdl/auton.h"

namespace autons {
void skills()
{
}

void nothing() {}

void smallZone(int side)
{
    okapi::Rate timer;
    armController->setTarget(0);
    intakes(1.0);
    driveController->setMaxVelocity(150);
    driveToPoint({ 36_in, 0_in });
    intakes(0);
    driveToPoint({ 12_in, 24_in }, true);
    intakes(1.0);
    driveToPoint({ 36_in, 24_in });
    driveToPoint({ 18_in, 24_in }, true);
    driveToPoint({ 12_in, 36_in });
    intake.moveRelative(-500, 100);
    timer.delayUntil(400_ms);
    trayController->flipDisable(false);
    trayController->setTarget(800);
    while (!trayController->isSettled()) {
        if (30 < trayController->getError() && trayController->getError() < 400) {
            intakes(0.6);
        } else {
            intakes(0);
        }
        timer.delayUntil(20_ms);
    }
    intakes(-0.6);
    driveModel->arcade(-.4, 0);
}

void bigZone(int side)
{
}
}