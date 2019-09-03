#ifndef _MBDL_DEVICES_H_
#define _MBDL_DEVICES_H_

#include "../api.h"
#include <memory>

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
    std::shared_ptr<pros::Motor> motor;

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
    std::shared_ptr<pros::Motor> raw();

    /**
	 * Sets the motor to specified power
	 * 
	 * @param pwr the power within [-1, 1] to set the output to
	 */
    void set(double pwr);
};

template <int num>
class MotorGroup : public Out {
private:
    std::shared_ptr<pros::Motor> motors[num];

public:
    /**
	 * Creates a MotorGroup object on the specified ports
	 * 
	 * @param list the list of motor ports
	 */
    MotorGroup(std::initializer_list<std::int8_t> list)
    {
        bool rev;
        std::initializer_list<std::int8_t>::iterator i;
        std::uint8_t mtr_num = 0;
        for (i = list.begin(); i < list.end(); i++) {
            if (*i < 0) {
                rev = true;
                motors[mtr_num] = std::make_shared<pros::Motor>(*i * -1, rev);
            } else {
                rev = false;
                motors[mtr_num] = std::make_shared<pros::Motor>(*i, rev);
            }
            mtr_num++;
        }
    }

    /**
	 * Returns a pointer to the specified pros::Motor object for additional functionality
	 * 
	 * @param i the index of the motor in the group
	 * @return the pointer to the pros::Motor object
	 */
    std::shared_ptr<pros::Motor> raw(std::uint8_t i)
    {
        return motors[i];
    }

    /**
	 * Sets the motors to specified power
	 * 
	 * @param pwr the power within [-1, 1] to set the output to
	 */
    void set(double pwr)
    {
        for (int i = 0; i < num; i++) {
            motors[i]->move_voltage(pwr * 12000);
        }
    }
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

    /**
	 * Gets the scaled poteniometer data
	 * 
	 * @return the scaled poteniometer value
	 */
    double get();

    /**
	 * Gets the raw poteniometer data
	 * 
	 * @return the raw potentiometer value in [0, 4095]
	 */
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

    /**
	 * Gets the scaled encoder data
	 * 
	 * @return the scaled encoder value
	 */
    double get();

    /**
	 * Gets the raw encoder data
	 * 
	 * @return the raw encoder value
	 */
    double raw();

    /**
	 * Resets the Encoder to zero
	 */
    void reset();
};

class MotorEncoder : public In {
private:
    std::shared_ptr<pros::Motor> motor;
    double scale;

public:
    /**
	 * Creates a MotorEncoder object
	 * 
	 * @param mtr the pointer to the pros::Motor whose encoder is being used
	 * @param sc the scale for the get() value
	 */
    MotorEncoder(std::shared_ptr<pros::Motor> mtr, double sc);

    /**
	 * Gets the scaled encoder data
	 * 
	 * @return the scaled encoder value
	 */
    double get();

    /**
	 * Gets the raw encoder data
	 * 
	 * @return the raw encoder value
	 */
    double raw();

    /**
	 * Resets the MotorEncoder value to zero
	 */
    void reset();
};
}
#endif