#include "main.h"

int8_t leftPorts[] = { 1, 2 };
int8_t rightPorts[] = { 9, 10 };

mbdl::devices::MotorGroup left(leftPorts, 2);
mbdl::devices::MotorGroup right(rightPorts, 2);

mbdl::devices::In* encoders[3] = {
    new mbdl::devices::MotorEncoder(left.raw(0), 1),
    new mbdl::devices::MotorEncoder(right.raw(0), 1),
    new mbdl::devices::Encoder(1, 2, 1)
};

void opcontrol()
{
    mbdl::drive::create(13.0, &left, &right, encoders);
    while (true) {
        pros::delay(10);
    }
}