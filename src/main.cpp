#include "main.h"

mbdl::devices::MotorGroup<2> left{ -1, -2 };
mbdl::devices::MotorGroup<2> right{ 9, 10 };

mbdl::devices::In* encoders[3] = {
    new mbdl::devices::Encoder(1, 2, -0.05672320068),
    new mbdl::devices::Encoder(3, 4, -0.05672320068),
    nullptr
};

void initialize()
{
    pros::c::serctl(SERCTL_DISABLE_COBS, NULL);
    mbdl::drive::create(8.0, &left, &right, encoders);
    std::cout << "flushing COBS\n";
}

void autonomous()
{
    mbdl::devices::MotorEncoder encoder(left.raw(0), 0.03490658503);
    //  mbdl::log::CSV full("/usd/full.csv", "Time (s), Distance (in)");
    mbdl::drive::tank(1, 1);
    int startTime = pros::millis();
    double data[3]{ 0, 0, '\n' };
    std::cout << "<FILE>\n";
    std::cout << "Time (s), Distance (in)\n";
    while (data[0] < 3000) {
        data[0] = pros::millis() - startTime;
        data[1] = encoder.get();
        std::cout << data[0] << "," << data[1] << '\n';
        //   full.add(data, false);
        pros::delay(10);
    }
    std::cout << "</FILE>\n";
    mbdl::drive::tank(0, 0);
    //full.add(mbdl::log::end, false);
    //full.close();
}

void opcontrol()
{
    pros::Controller main(pros::E_CONTROLLER_MASTER);
    while (true) {
        mbdl::drive::arcade(main.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0, -main.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0);
        // mbdl::log::println<std::string>("in driver" + pros::millis());
        std::cout << "coords " << encoders[0]->get() << ", " << encoders[1]->get() << '\n';
        pros::delay(10);
    }
}