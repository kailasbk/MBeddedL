#ifndef _MBDL_DEVICES_H_
#define _MBDL_DEVICES_H_

#include "../api.h"

namespace mbdl::devices {
class In {
public:
    /**
	 * Gets the filtered sensor data
	 * 
	 * @return the modified sensor value
	 */
    virtual double get() = 0;

    /**
	 * Gets the raw sensor data
	 * 
	 * @return the raw, unmodified sensor value
	 */
    virtual double raw() = 0;
};

class Out {
public:
    /**
	 * Sets the output to specified power
	 * 
	 * @param pwr the power within [-1, 1] to set the output to
	 */
    virtual void set(double pwr) = 0;
};

class Motor : public Out {
private:
    pros::Motor* motor;

public:
    /**
	 * Creates a Motor object on the specified port
	 * 
	 * @param port the motor port, with negative numbers denoting a reversed motor
	 */
    Motor(std::int8_t port);

    /**
	 * Returns a pointer to the pros::Motor object for additional functionality
	 * 
	 * @return the pointer to the pros::Motor object
	 */
    pros::Motor* raw();

    void set(double pwr);
};

class MotorGroup : public Out {
private:
    pros::Motor** motors;
    std::uint8_t num;

public:
    /**
	 * Creates a MotorGroup object on the specified ports
	 * 
	 * @param port the array of motor ports, with negative numbers denoting a reversed motor
	 * @param num the number of motors in the MotorGroup
	 */
    MotorGroup(std::int8_t port[], std::uint8_t num);

    /**
	 * Returns a pointer to the specified pros::Motor object for additional functionality
	 * 
	 * @param i the index of the motor in the group
	 * @return the pointer to the pros::Motor object
	 */
    pros::Motor* raw(std::uint8_t i);

    void set(double pwr);
};

class Potentiometer : public In {
private:
    std::uint8_t port;
    double scale, shift;

public:
    /**
	 * Creates a Poteniometer object
	 * 
	 * @param port the ADI port the sensor in on
	 * @param scale the scale for the get() value
	 * @param shift the shift for the get() value
	 */
    Potentiometer(std::uint8_t port, double scale, double shift);

    double get();

    double raw();
};

class Encoder : public In {
private:
    pros::c::adi_encoder_t enc;
    double scale;

public:
    /**
	 * Creates an Encoder object
	 * 
	 * @param one the ADI port for the first wire
	 * @param two the ADI port fot the second wire
	 * @param scale the scale for the get() value
	 */
    Encoder(std::uint8_t one, std::uint8_t two, double scale);

    double get();

    double raw();

    /**
	 * Resets the Encoder to zero
	 */
    void reset();
};

class MotorEncoder : public In {
private:
    pros::Motor* motor;
    double scale;

public:
    /**
	 * Creates a MotorEncoder object
	 * 
	 * @param mtr the pointer to the pros::Motor whose encoder is being used
	 * @param sc the scale for the get() value
	 */
    MotorEncoder(pros::Motor* mtr, double sc);

    double get();

    double raw();

    /**
	 * Resets the MotorEncoder value to zero
	 */
    void reset();
};
}
#endif