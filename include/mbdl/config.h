#pragma once

#include "okapi/api.hpp"
#include "pros/apix.h"
using namespace okapi::literals;

// robot motors
extern okapi::MotorGroup arm;
extern okapi::Motor tray;
extern okapi::Motor left;
extern okapi::Motor right;
extern okapi::Motor strafe;
extern okapi::MotorGroup intake;

// robot adi ports
extern okapi::ADIButton trayLimit;
extern okapi::ADIButton armLimit;
extern okapi::ADIButton allianceButton;
extern okapi::ADIButton autonButton;

// robot controllers
extern std::shared_ptr<okapi::OdomChassisController> driveController;
extern std::shared_ptr<okapi::SkidSteerModel> driveModel;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> trayController;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> armController;

void intakes(double power);
