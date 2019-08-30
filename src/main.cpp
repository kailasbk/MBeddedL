#include "main.h"

mbdl::devices::MotorGroup left{ 1, 2 };
mbdl::devices::MotorGroup right{ 9, 10 };

mbdl::devices::In* encoders[3] = {
    new mbdl::devices::MotorEncoder(left.raw(0), 1),
    new mbdl::devices::MotorEncoder(right.raw(0), 1),
    nullptr
};

void initialize()
{
    mbdl::drive::create(13, &left, &right, encoders);
}

void autonomous()
{
}

void opcontrol()
{
    pros::Controller main(pros::E_CONTROLLER_MASTER);
    while (true) {
        mbdl::drive::arcade(main.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), -main.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
        pros::delay(10);
    }
}