#include "main.h"
#include "mbdl/api.h"

okapi::Controller controller;

#define RED 0
#define BLUE 1

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
    // turn on auton selector (using LVGL in the future)
    bool selected = false;

    while (!selected) {
        if (alliance == RED) {
            pros::lcd::print(0, "Alliance: Red");
        } else if (alliance == BLUE) {
            pros::lcd::print(0, "Alliance: Blue");
        }

        switch (auton) {
        case 0:
            break;
        default:
            pros::lcd::print(1, "Auton: Nothing");
            break;
        }
    }
}

void autonomous()
{
    // +x is forward, +y is right, 0 degrees along +x going counterclockwise
    driveController->setMaxVelocity(100);
    driveController->driveToPoint({ 3_ft, 0_ft });

    driveController->setMaxVelocity(200);
    driveController->driveToPoint({ -2_ft, 0_ft });

    driveController->turnAngle({ 135_deg });
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

        if (controller.getDigital(okapi::ControllerDigital::B)) {
            trayController->flipDisable(false);
            trayController->setMaxVelocity(50);
            trayController->setTarget(800);
            if (30 < trayController->getError() && trayController->getError() < 400) {
                intake.moveVoltage(0.5 * okapi::v5MotorMaxVoltage);
            } else if (trayController->isSettled() && controller.getAnalog(okapi::ControllerAnalog::leftY) < -.5) {
                intake.moveVoltage(-0.6 * okapi::v5MotorMaxVoltage);
                driveModel->arcade(-.4, 0);
            } else {
                intake.moveVoltage(0);
            }
        } else {
            trayController->flipDisable(true);
            if (controller.getDigital(okapi::ControllerDigital::R2) && tray.getPosition() > 360) {
                intake.moveVoltage(-0.6 * okapi::v5MotorMaxVoltage);
            } else if (controller.getDigital(okapi::ControllerDigital::R2)) {
                intake.moveVoltage(-okapi::v5MotorMaxVoltage);
            } else if (controller.getDigital(okapi::ControllerDigital::R1)) {
                intake.moveVoltage(okapi::v5MotorMaxVoltage);
            } else {
                intake.moveVoltage(0);
            }

            if (controller.getDigital(okapi::ControllerDigital::L1)) {
                tray.moveAbsolute(330, 90);
                arm.moveVoltage(controller.getAnalog(okapi::ControllerAnalog::rightY) * okapi::v5MotorMaxVoltage);
            } else {
                tray.moveVoltage(controller.getAnalog(okapi::ControllerAnalog::rightY) * okapi::v5MotorMaxVoltage);
                arm.moveVoltage(0);
            }

            if (controller.getDigital(okapi::ControllerDigital::L2)) {
                strafe.moveVoltage(controller.getAnalog(okapi::ControllerAnalog::rightX) * okapi::v5MotorMaxVoltage);
                right.moveVoltage(-controller.getAnalog(okapi::ControllerAnalog::rightX) * okapi::v5MotorMaxVoltage / 2);
                left.moveVoltage(controller.getAnalog(okapi::ControllerAnalog::rightX) * okapi::v5MotorMaxVoltage / 2);
            } else {
                right.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
                left.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
                driveModel->arcade(
                    controller.getAnalog(okapi::ControllerAnalog::leftY),
                    controller.getAnalog(okapi::ControllerAnalog::leftX));
                strafe.moveVoltage(-controller.getAnalog(okapi::ControllerAnalog::leftX) * okapi::v5MotorMaxVoltage);
            }
        }
        timer.delay(50_Hz);
    }
}