#include "main.h"

mbdl::devices::MotorGroup<2> left{ -1, -2 };
mbdl::devices::MotorGroup<2> right{ 9, 10 };

mbdl::devices::In* encoders[3] = {
    new mbdl::devices::Encoder(1, 2, -0.05672320068),
    new mbdl::devices::Encoder(3, 4, -0.05672320068),
    nullptr
};

mbdl::display::Style style(&lv_style_pretty);

mbdl::display::Tabs tabs{ "Monitor", "Odom", "File" };
mbdl::display::Button btn("button", (lv_action_t)NULL, tabs[0]);

void initialize()
{
    pros::c::serctl(SERCTL_DISABLE_COBS, NULL);
    mbdl::drive::create(8.0, &left, &right, encoders);
    std::cout << "flushing COBS\n";
}

void autonomous()
{
    mbdl::log::CSV full("full.csv", "Time (s), Distance (in)");
    mbdl::drive::tank(1, 1);
    int startTime = pros::millis();
    double data[2]{ 0, 0 };
    while (data[0] < 3000) {
        data[0] = pros::millis() - startTime;
        data[1] = encoders[0]->get();
        full << data[0] << ',' << data[1] << '\n';
        pros::delay(10);
    }
    mbdl::drive::tank(0, 0);
    full << '\n';
    full.close();
    mbdl::log::printfile("full.csv");
}

void opcontrol()
{
    pros::Controller main(pros::E_CONTROLLER_MASTER);
    while (true) {
        mbdl::drive::arcade(main.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0, -main.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0);
        std::cout << "coords " << encoders[0]->get() << ", " << encoders[1]->get() << '\n';
        pros::delay(10);
    }
}