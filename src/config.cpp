#include "mbdl/config.h"

okapi::MotorGroup arm{ 1, -2 };
okapi::Motor tray(10, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor left(17);
okapi::Motor right(-20);
okapi::Motor strafe(-18);
okapi::MotorGroup intake{ 5, -7 };

okapi::ADIButton trayLimit('b');
okapi::ADIButton armLimit('c');
okapi::ADIButton autonButton('h');

okapi::ChassisScales driveDimensions({ 3.25_in, 11.75_in, 5.875_in }, okapi::imev5GreenTPR);

std::shared_ptr<okapi::OdomChassisController> driveController = okapi::ChassisControllerBuilder()
                                                                    .withMotors(left, right)
                                                                    .withGains({ 0, 0, 0, .5 }, { 0, 0, 0, .5 })
                                                                    .withDimensions(okapi::AbstractMotor::gearset::green, driveDimensions)
                                                                    .withSensors(left.getEncoder(), right.getEncoder(), strafe.getEncoder())
                                                                    .withOdometry(okapi::StateMode::FRAME_TRANSFORMATION)
                                                                    .buildOdometry();

std::shared_ptr<okapi::SkidSteerModel> driveModel(static_cast<okapi::SkidSteerModel*>(driveController->getModel().get()));

std::shared_ptr<okapi::AsyncPositionController<double, double>> trayController = okapi::AsyncPosControllerBuilder()
                                                                                     .withMotor(tray)
                                                                                     .build();

std::shared_ptr<okapi::AsyncPositionController<double, double>> armController = okapi::AsyncPosControllerBuilder()
                                                                                    .withMotor(arm)
                                                                                    .build();