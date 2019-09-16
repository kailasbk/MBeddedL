#ifndef _MBDL_CONTROLLER_H_
#define _MBDL_CONTROLLER_H_

#include "../api.h"

namespace mbdl::controller {
inline namespace main {
    /**
	 * Returns the left analog stick x value
	 * 
	 * @return value from [-1, 1]
	 */
    double leftX();

    /**
	 * Returns the left analog stick y value
	 * 
	 * @return value from [-1, 1]
	 */
    double leftY();

    /**
	 * Returns the right analog stick x value
	 * 
	 * @return value from [-1, 1]
	 */
    double rightX();

    /**
	 * Returns the right analog stick y value
	 * 
	 * @return value from [-1, 1]
	 */
    double rightY();

    /**
	 * Returns the state of the left trigger
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool triggerL();

    /**
	 * Returns the state of the left button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool buttonL();

    /**
	 * Returns the state of the right trigger
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool triggerR();

    /**
	 * Returns the state of the right button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool buttonR();

    /**
	 * Returns the state of the up directional button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool up();

    /**
	 * Returns the state of the down directional button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool down();

    /**
	 * Returns the state of the left directional button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool left();

    /**
	 * Returns the state of the right directional button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool right();

    /**
	 * Returns the state of the x button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool x();

    /**
	 * Returns the state of the y button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool y();

    /**
	 * Returns the state of the a button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool a();

    /**
	 * Returns the state of the b button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool b();
}
namespace secondary {
    /**
	 * Returns the left analog stick x value
	 * 
	 * @return value from [-1, 1]
	 */
    double leftX();

    /**
	 * Returns the left analog stick y value
	 * 
	 * @return value from [-1, 1]
	 */
    double leftY();

    /**
	 * Returns the right analog stick x value
	 * 
	 * @return value from [-1, 1]
	 */
    double rightX();

    /**
	 * Returns the right analog stick y value
	 * 
	 * @return value from [-1, 1]
	 */
    double rightY();

    /**
	 * Returns the state of the left trigger
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool triggerL();

    /**
	 * Returns the state of the left button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool buttonL();

    /**
	 * Returns the state of the right trigger
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool triggerR();

    /**
	 * Returns the state of the right button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool buttonR();

    /**
	 * Returns the state of the up directional button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool up();

    /**
	 * Returns the state of the down directional button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool down();

    /**
	 * Returns the state of the left directional button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool left();

    /**
	 * Returns the state of the right directional button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool right();

    /**
	 * Returns the state of the x button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool x();

    /**
	 * Returns the state of the y button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool y();

    /**
	 * Returns the state of the a button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool a();

    /**
	 * Returns the state of the b button
	 * 
	 * @return the state where pressed is true and released is false
	 */
    bool b();
}
}

#endif