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
mbdl::display::Label monitor("this is the monitor tab\n"
                             "this is another line",
    tabs[0]);

lv_res_t filefunc(lv_obj_t* obj)
{
    mbdl::log::printfile("log.csv");
}

mbdl::display::Button filebtn("Send file", filefunc, tabs[2]);

void initialize()
{
    pros::c::serctl(SERCTL_DISABLE_COBS, NULL);
    mbdl::drive::create(8.0, &left, &right, encoders);
    std::cout << "flushing COBS\n";
}

void autonomous()
{
    mbdl::log::CSV log("log.csv", "Time (s), Distance (in)");
    mbdl::drive::tank(1, 1);
    int startTime = pros::millis();
    double data[3]{ 0, 0, '\n' };
    while (data[0] < 3000) {
        data[0] = pros::millis() - startTime;
        data[1] = encoders[0]->get();
        // log << data[0] << ',' << data[1] << '\n';
        log.add(data, false);
        pros::delay(10);
    }
    mbdl::drive::tank(0, 0);
    log << '\n';
    log.close();
}

void opcontrol()
{
    while (true) {
        mbdl::drive::arcade(mbdl::controller::leftY(), -mbdl::controller::leftX());
        pros::delay(10);
    }
}