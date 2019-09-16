#include "mbdl/controller.h"

namespace mbdl::controller {
inline namespace main {
    double leftX()
    {
        return pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0;
    }

    double leftY()
    {
        return pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;
    }

    double rightX()
    {
        return pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;
    }

    double rightY()
    {
        return pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0;
    }

    bool triggerL()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_L2);
    }

    bool buttonL()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_L1);
    }

    bool triggerR()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_R2);
    }

    bool buttonR()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_R1);
    }

    bool up()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_UP);
    }

    bool down()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_DOWN);
    }

    bool left()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_LEFT);
    }

    bool right()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_RIGHT);
    }

    bool x()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_X);
    }

    bool y()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_Y);
    }

    bool a()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_A);
    }

    bool b()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_B);
    }
}
namespace secondary {
    double leftX()
    {
        return pros::c::controller_get_analog(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0;
    }

    double leftY()
    {
        return pros::c::controller_get_analog(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;
    }

    double rightX()
    {
        return pros::c::controller_get_analog(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;
    }

    double rightY()
    {
        return pros::c::controller_get_analog(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0;
    }

    bool triggerL()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_L2);
    }

    bool buttonL()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_L1);
    }

    bool triggerR()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_R2);
    }

    bool buttonR()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_R1);
    }

    bool up()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_UP);
    }

    bool down()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_DOWN);
    }

    bool left()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_LEFT);
    }

    bool right()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_RIGHT);
    }

    bool x()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_X);
    }

    bool y()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_Y);
    }

    bool a()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_A);
    }

    bool b()
    {
        return pros::c::controller_get_digital(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_DIGITAL_B);
    }
}
}