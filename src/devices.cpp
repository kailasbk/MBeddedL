#include "main.h"

mbdl::devices::Motor::Motor(int8_t port)
{
    bool rev = false; // by default motor isn't reversed
    if (port < 0) { // if port in negative
        rev = true; // reverse the motor
        port = port * -1;
    }
    motor = new pros::Motor(port, rev); // contruct the new pros::Motor on the heap and store the address
}

pros::Motor* mbdl::devices::Motor::raw()
{
    return motor; // return the pointer to the pros::Motor object
}

void mbdl::devices::Motor::set(double pwr)
{
    motor->move_voltage(pwr * 12000); // set motor to pwr
}

mbdl::devices::MotorGroup::MotorGroup(int8_t port[], uint8_t num)
{
    this->num = num;
    bool rev; // boolean to track motor reversal
    motors = new pros::Motor*[num]; // allocate an array of pros::Motor pointers
    for (int i = 0; i < num; i++) { // for each motor
        if (port[i] < 0) { // if port in negative
            rev = true; // reverse is true
            port[i] = port[i] * -1; // make port positive
        } else {
            rev = false; // reverse is false
        }
        motors[i] = new pros::Motor(port[i], rev); // allocate pros::Motor and store address
    }
}

pros::Motor* mbdl::devices::MotorGroup::raw(uint8_t i)
{
    return motors[i]; // return pointer to i-th motor
}

void mbdl::devices::MotorGroup::set(double pwr)
{
    for (int i = 0; i < num; i++) { // for each motor
        motors[i]->move_voltage(pwr * 12000); // set motor to pwr
    }
}

mbdl::devices::Potentiometer::Potentiometer(std::uint8_t port, double scale, double shift)
{
    // init all variables to specified values
    this->port = port;
    this->scale = scale;
    this->shift = shift;
}

double mbdl::devices::Potentiometer::get()
{
    return (pros::c::adi_analog_read(port) * scale) + shift; // return the scale and shifted sensor value
}

double mbdl::devices::Potentiometer::raw()
{
    return pros::c::adi_analog_read(port); // return the raw sensor value
}

mbdl::devices::Encoder::Encoder(std::uint8_t one, std::uint8_t two, double scale)
{
    enc = pros::c::adi_encoder_init(one, two, false); // initialize the encoder
    this->scale = scale; // set the scale
}

double mbdl::devices::Encoder::raw()
{
    return pros::c::adi_encoder_get(enc); // return the raw encoder value
}

double mbdl::devices::Encoder::get()
{
    return pros::c::adi_encoder_get(enc) * scale; // return the scaled encoder value
}

void mbdl::devices::Encoder::reset()
{
    pros::c::adi_encoder_reset(enc); // reset the encoder
}

mbdl::devices::MotorEncoder::MotorEncoder(pros::Motor* mtr, double sc)
{
    motor = mtr;
    scale = sc;
}

double mbdl::devices::MotorEncoder::get()
{
    return motor->get_position() * scale;
}

double mbdl::devices::MotorEncoder::raw()
{
    return motor->get_position();
}

void mbdl::devices::MotorEncoder::reset()
{
    motor->tare_position();
}