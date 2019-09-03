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
    motor = std::make_shared<pros::Motor>(port, rev); // contruct the new pros::Motor on the heap and store the address
}

std::shared_ptr<pros::Motor> Motor::raw()
{
    return motor; // return the pointer to the pros::Motor object
}

void Motor::set(double pwr)
{
    motor->move_voltage(pwr * 12000); // set motor to pwr
}

Potentiometer::Potentiometer(std::uint8_t port, double scale, double shift)
{
    this->port = port;
    this->scale = scale;
    this->shift = shift;
}

double Potentiometer::get()
{
    return (pros::c::adi_analog_read(port) * scale) + shift;
}

double Potentiometer::raw()
{
    return pros::c::adi_analog_read(port);
}

Encoder::Encoder(std::uint8_t one, std::uint8_t two, double scale)
{
    enc = pros::c::adi_encoder_init(one, two, false);
    this->scale = scale;
}

double Encoder::raw()
{
    return pros::c::adi_encoder_get(enc);
}

double Encoder::get()
{
    return pros::c::adi_encoder_get(enc) * scale;
}

void Encoder::reset()
{
    pros::c::adi_encoder_reset(enc);
}

MotorEncoder::MotorEncoder(std::shared_ptr<pros::Motor> mtr, double sc)
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