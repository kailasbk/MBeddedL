#include "main.h"

mbdl::devices::MotorGroup<2> left{ 1, 2 };
mbdl::devices::MotorGroup<2> right{ 9, 10 };

mbdl::devices::In* encoders[3] = {
    new mbdl::devices::MotorEncoder(left.raw(0), 0.03490658503),
    new mbdl::devices::MotorEncoder(right.raw(0), 0.03490658503),
    nullptr
};

void initialize()
{
    pros::c::serctl(SERCTL_DISABLE_COBS, NULL);
    // mbdl::drive::create(13, &left, &right, encoders);
}

void autonomous()
{
    mbdl::devices::MotorEncoder encoder(left.raw(0), 0.03490658503);
    mbdl::log::CSV full("/usd/full.csv", "Time (s), Distance (in)");
    left.set(1);
    right.set(1);
    int startTime = pros::millis();
    double data[3]{ 0, 0, '\n' };
    for (int i = 0; i < 3000; i++) {
        data[0] = pros::millis() - startTime;
        data[1] = encoder.get();
        full.add(data, false);
        pros::delay(10);
    }
    left.set(0);
    right.set(0);
    full.add(mbdl::log::end, false);
    full.close();

    pros::delay(3000);

    mbdl::drive::create(13, &left, &right, encoders);
    mbdl::log::CSV slewed("/usd/slewed.csv", "Time (s), Distance (in)");
    mbdl::drive::tank(1, 1);
    startTime = pros::millis();
    data[0] = 0;
    data[1] = 0;
    for (int i = 0; i < 3000; i++) {
        data[0] = pros::millis() - startTime;
        data[1] = encoder.get();
        full.add(data, false);
        pros::delay(10);
    }
    slewed.add(mbdl::log::end, false);
    slewed.close();
}

void opcontrol()
{
    pros::Controller main(pros::E_CONTROLLER_MASTER);
    mbdl::log::println("In opcontrol");
    while (true) {
        mbdl::drive::arcade(main.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), -main.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
        mbdl::log::println("Time: " + pros::millis());
        pros::delay(10);
    }
}