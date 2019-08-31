#include "mbdl/devices.h"
#include "api.h"

namespace mbdl::devices {
Motor::Motor(int8_t port)
{
    bool rev = false; // by default motor isn't reversed
    if (port < 0) { // if port in negative
        rev = true; // reverse the motor
        port = port * -1;
    }
    motor = new pros::Motor(port, rev); // contruct the new pros::Motor on the heap and store the address
}

pros::Motor* Motor::raw()
{
    return motor; // return the pointer to the pros::Motor object
}

void Motor::set(double pwr)
{
    motor->move_voltage(pwr * 12000); // set motor to pwr
}

MotorGroup::MotorGroup(int8_t port[], uint8_t num)
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

MotorGroup::MotorGroup(std::initializer_list<std::int8_t> list)
{
    num = list.size();
    bool rev; // boolean to track motor reversal
    motors = new pros::Motor*[num]; // allocate an array of pros::Motor pointers
    std::initializer_list<std::int8_t>::iterator i;
    std::uint8_t mtr_num = 0;
    for (i = list.begin(); i < list.end(); i++) { // for each motor
        if (*i < 0) { // if port in negative
            rev = true; // reverse is true
            motors[mtr_num] = new pros::Motor(*i * -1, rev); // allocate pros::Motor and store address
        } else {
            rev = false; // reverse is false
            motors[mtr_num] = new pros::Motor(*i, rev); // allocate pros::Motor and store address
        }
        mtr_num++;
    }
}

pros::Motor* MotorGroup::raw(uint8_t i)
{
    return motors[i]; // return pointer to i-th motor
}

void MotorGroup::set(double pwr)
{
    for (int i = 0; i < num; i++) { // for each motor
        motors[i]->move_voltage(pwr * 12000); // set motor to pwr
    }
}

Potentiometer::Potentiometer(std::uint8_t port, double scale, double shift)
{
    // init all variables to specified values
    this->port = port;
    this->scale = scale;
    this->shift = shift;
}

double Potentiometer::get()
{
    return (pros::c::adi_analog_read(port) * scale) + shift; // return the scale and shifted sensor value
}

double Potentiometer::raw()
{
    return pros::c::adi_analog_read(port); // return the raw sensor value
}

Encoder::Encoder(std::uint8_t one, std::uint8_t two, double scale)
{
    enc = pros::c::adi_encoder_init(one, two, false); // initialize the encoder
    this->scale = scale; // set the scale
}

double Encoder::raw()
{
    return pros::c::adi_encoder_get(enc); // return the raw encoder value
}

double Encoder::get()
{
    return pros::c::adi_encoder_get(enc) * scale; // return the scaled encoder value
}

void Encoder::reset()
{
    pros::c::adi_encoder_reset(enc); // reset the encoder
}

MotorEncoder::MotorEncoder(pros::Motor* mtr, double sc)
{
    motor = mtr;
    scale = sc;
}

double MotorEncoder::get()
{
    return motor->get_position() * scale;
}

double MotorEncoder::raw()
{
    return motor->get_position();
}

void MotorEncoder::reset()
{
    motor->tare_position();
}
}