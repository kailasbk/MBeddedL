#ifndef _MBDL_DRIVE_H_
#define _MBDL_DRIVE_H_

#include "../api.h"
#include "mbdl/devices.h"
#include "mbdl/math.h"

namespace mbdl::drive {
/**** Robot Position Variables ****/
extern math::Vector<2> position;
extern double theta;
extern math::Vector<2> displacement;
extern math::Vector<2> heading;

/**** BUFFER MODE MACROS ****/
#define TANK 0
#define ARCADE 1
#define TURN 2
#define ARC 3
#define LINE 4
#define TO 5

extern pros::Task* taskPtr;

/**
 * Task for the tracking and drive control
 * 
 * @param params the extra pointer to the data used by the task
 */
void controlTask(void* params);

/**
 * Initializes the drivetrain in tank drive and 3 encoder odometry
 * 
 * @param w the width of the drivetrain
 * @param l the pointer to the left side Motor or MotorGroup
 * @param r the pointer to the right sides Motor or MotorGroup
 * @param enc the array of pointers to the encoder objects
 */
void create(double w, devices::Out* l, devices::Out* r, devices::In* enc[3]);

/**
 * Sets the drivetrain using tank control
 * 
 * @param left the power within [-1, 1] for the left side
 * @param right the power within [-1, 1] for the right side
 */
void tank(double left, double right);

/**
 * Sets the drivetrain using arcade control
 * 
 * @param pwr the forward power within [-1, 1]
 * @param turn the turning power within [-1, 1]
 */
void arcade(double pwr, double turn);

/**
 * Turns the drivetrain arounds its center to the specified angle
 * 
 * @param goal the desired angle in radians
 */
void turn(double goal);

/**
 * Moves the robot in an arc
 * 
 * @param angle the angle of the arc in radians
 * @param radius the radius of the arc in inches
 */
void arc(double angle, double radius);

/**
 * Move the robot in a straight line
 * 
 * @param distance in inches
 */
void line(double distance);

/**
 * Moves the drivetrain to the specified point
 * 
 * @param goal the desired coordinates in inches
 */
void to(math::Vector<2> goal);

/**
 * States whether the robot has come to rest
 */
bool isSettled();
}

#endif