#include "main.h"
#include "mbdl/api.h"

okapi::Controller controller;

int alliance = 0;
int auton = 0;

void initialize()
{
    // initialize display
    pros::lcd::initialize();

    // disable serial encoding
    pros::c::serctl(SERCTL_DISABLE_COBS, NULL);
    std::cout << "\n"; // flushing COBS
    // set okapi logger
    okapi::Logger::setDefaultLogger(
        std::make_shared<okapi::Logger>(
            okapi::TimeUtilFactory::createDefault().getTimer(),
            stdout,
            okapi::Logger::LogLevel::info));

    intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    tray.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    arm.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    strafeOff();
}

void competition_initialize()
{
    okapi::Rate timer;
    // turn on auton selector (using LVGL in the future)
    bool selected = false;

    while (!selected) {
        if (alliance == RED) {
            pros::lcd::print(0, "Alliance: Red");
        } else if (alliance == BLUE) {
            pros::lcd::print(0, "Alliance: Blue");
        } else if (alliance == SKILLS) {
            pros::lcd::print(0, "Alliance: Skills");
        }

        switch (auton) {
        case 0:
            break;
        default:
            pros::lcd::print(1, "Auton: Nothing");
            break;
        }

        if (autonButton.isPressed()) {
            auton++;
            if (auton > 0000) {
                auton = 0;
            }
            while (autonButton.isPressed()) {
                timer.delayUntil(20_ms);
            }
        } else if (allianceButton.isPressed()) {
            alliance++;
            if (alliance > 2) {
                alliance = 0;
            }
            while (allianceButton.isPressed()) {
                timer.delayUntil(20_ms);
            }
        }

        timer.delayUntil(20_ms);
    }
}

void autonomous()
{
    strafeOn();
    if (alliance == SKILLS) {
        autons::skills();
    } else {
        switch (auton) {
        case 0:
            autons::nothing();
            break;
        case 1:
            autons::smallZone(alliance);
            break;
        case 2:
            autons::bigZone(alliance);
            break;
        default:
            autons::nothing();
            break;
        }
    }
    strafeOff();
}

void opcontrol()
{
    okapi::Rate timer;
    while (true) {

        /** DRIVER CONTROLS
		 * intake in/out => right triggers
		 * arcade drive => left joystick
		 * lift => right joystick with shift key(with hold in dead zone)
		 * strafe => right joystick (shift key off)
		 * tray =>
		 * 	- manual => right joystick with shift key
		 * 	- automatic =>
		 * 		in => Y button
		 * 		out => X button
		 */

        pros::lcd::print(0, "X: %f", driveController->getState().x.convert(okapi::inch));
        pros::lcd::print(1, "Y: %f", driveController->getState().y.convert(okapi::inch));
        pros::lcd::print(2, "Theta: %f", driveController->getState().theta.convert(okapi::degree));

        if (trayLimit.isPressed()) {
            trayController->tarePosition();
            pros::lcd::print(3, "Tray limit pressed");
        } else {
            pros::lcd::print(3, "Tray value: %f", trayController->getProcessValue());
        }

        if (armLimit.isPressed()) {
            armController->tarePosition();
            pros::lcd::print(4, "Arm limit pressed");
        } else {
            pros::lcd::print(4, "Arm value: %f", armController->getProcessValue());
        }

        pros::lcd::print(5, "tray target: %f", trayController->getTarget());

        if (controller.getDigital(okapi::ControllerDigital::B)) {
            trayController->flipDisable(false);
            trayController->setTarget(800);
            if (30 < trayController->getError() && trayController->getError() < 400) {
                intakes(0.6);
            } else if (trayController->isSettled() && controller.getAnalog(okapi::ControllerAnalog::leftY) < -.5) {
                intakes(-0.6);
                driveModel->arcade(-.4, 0);
            } else {
                intakes(0);
            }
        } else {
            if (controller.getDigital(okapi::ControllerDigital::R2)) {
                intakes(-1.0);
            } else if (controller.getDigital(okapi::ControllerDigital::R1)) {
                intakes(1.0);
            } else {
                intakes(0);
            }

            if (controller.getDigital(okapi::ControllerDigital::up)) {
                trayController->flipDisable(false);
                trayController->setTarget(330);
            } else if (controller.getDigital(okapi::ControllerDigital::down)) {
                trayController->flipDisable(false);
                trayController->setTarget(0);
            } else if (abs(controller.getAnalog(okapi::ControllerAnalog::rightY)) > .05 && !controller.getDigital(okapi::ControllerDigital::L1)) {
                if (!trayController->isDisabled()) {
                    trayController->flipDisable(true);
                }
                tray.controllerSet(controller.getAnalog(okapi::ControllerAnalog::rightY));
            }

            if (controller.getDigital(okapi::ControllerDigital::X)) {
                trayController->flipDisable(false);
                trayController->setTarget(330);
                armController->flipDisable(false);
                armController->setTarget(0000);
            } else if (controller.getDigital(okapi::ControllerDigital::Y)) {
                trayController->flipDisable(false);
                trayController->setTarget(330);
                armController->flipDisable(false);
                armController->setTarget(0000);
            } else if (controller.getDigital(okapi::ControllerDigital::L1)) {
                if (!armController->isDisabled()) {
                    armController->flipDisable(true);
                }
                tray.controllerSet(controller.getAnalog(okapi::ControllerAnalog::rightY));
            }

            if (controller.getDigital(okapi::ControllerDigital::L2)) {
                double power = controller.getAnalog(okapi::ControllerAnalog::leftX) * okapi::v5MotorMaxVoltage;
                strafe.moveVoltage(power);
                driveModel->tank(power / 2, -power / 2);
            } else {
                driveModel->arcade(
                    controller.getAnalog(okapi::ControllerAnalog::leftY),
                    controller.getAnalog(okapi::ControllerAnalog::leftX));
                strafe.moveVoltage((right.getVoltage - left.getVoltage()) / 2);
            }
        }
        timer.delay(50_Hz);
    }
}