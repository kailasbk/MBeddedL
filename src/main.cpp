#include "main.h"

okapi::MotorGroup lift{ 1, 2 };
okapi::Motor tray(10, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor left(17);
okapi::Motor right(-20);
okapi::Motor strafe(18);
okapi::MotorGroup intake{ 8, -7 };

std::shared_ptr<okapi::OdomChassisController> driveController
    = okapi::ChassisControllerBuilder()
          .withMotors(left, right, strafe)
          // 200rpm, 3.25in wheels on 11.5in width, 3.25in middle wheel 6in from center, green gearset tpr
          .withDimensions(okapi::AbstractMotor::gearset::green, { { 3.25_in, 12.0_in, 1.5_in, 3.25_in }, okapi::imev5GreenTPR })
          .withOdometry(okapi::StateMode::FRAME_TRANSFORMATION)
          .buildOdometry();

std::shared_ptr<okapi::HDriveModel> driveModel(static_cast<okapi::HDriveModel*>(driveController->getModel().get()));

okapi::Controller controller;

void initialize()
{
    // initialize display
    mbdl::display::lcd::on();

    // disable serial encoding
    pros::c::serctl(SERCTL_DISABLE_COBS, NULL);
    std::cout << "\n"; // flushing COBS

    intake.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}

void competition_initialize()
{
}

void autonomous()
{
    // +x is forward, +y is right, 0 degrees along +x going counterclockwise
    driveController->setMaxVelocity(100);
    driveController->driveToPoint({ 3_ft, 0_ft });

    driveController->setMaxVelocity(200);
    driveController->driveToPoint({ -2_ft, 0_ft });

    driveController->turnAngle({ 135_deg })
}

void opcontrol()
{
    okapi::Rate timer;
    while (true) {

        /** DRIVER CONTROLS
		 * intake in/out => right triggers
		 * arcade drive => left joystick
		 * lift => right joystick (with hold in dead zone)
		 * strafe => left and right arrow button
		 * tray =>
		 * 	- manual => left triggers
		 * 	- automatic =>
		 * 		in => Y button
		 * 		out => X button
		 */

        if (controller.getDigital(okapi::ControllerDigital::A)) {
            intake.moveVoltage(-1.0 * okapi::v5MotorMaxVoltage);
        } else if (controller.getDigital(okapi::ControllerDigital::R2)) {
            intake.moveVoltage(-.7 * okapi::v5MotorMaxVoltage);
        } else if (controller.getDigital(okapi::ControllerDigital::R1)) {
            intake.moveVoltage(.7 * okapi::v5MotorMaxVoltage);
        } else {
            intake.moveVoltage(0);
        }

        if (controller.getDigital(okapi::ControllerDigital::L2)) {
            tray.moveVoltage(-.75 * okapi::v5MotorMaxVoltage);
        } else if (controller.getDigital(okapi::ControllerDigital::L1)) {
            tray.moveVoltage(.75 * okapi::v5MotorMaxVoltage);
        } else {
            tray.moveVoltage(controller.getAnalog(okapi::ControllerAnalog::rightY) * okapi::v5MotorMaxVoltage); // change to zero once lift added
        }

        if (controller.getDigital(okapi::ControllerDigital::right)) {
            strafe.moveVoltage(okapi::v5MotorMaxVoltage);
            right.moveVoltage(-120);
            left.moveVoltage(120);
        } else if (controller.getDigital(okapi::ControllerDigital::left)) {
            strafe.moveVoltage(-okapi::v5MotorMaxVoltage);
            right.moveVoltage(120);
            left.moveVoltage(-120);
        } else {
            driveModel->arcade(
                controller.getAnalog(okapi::ControllerAnalog::leftY),
                controller.getAnalog(okapi::ControllerAnalog::leftX));
        }

        // lift.moveVoltage(controller.getAnalog(okapi::ControllerAnalog::rightY) * okapi::v5MotorMaxVoltage);

        timer.delay(50_Hz);
    }
}