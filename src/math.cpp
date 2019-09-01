#include "mbdl/math.h"

namespace mbdl::math {
double equiv(double angle)
{
    if (angle > 0) { // if angle is positive
        return angle - (2 * PI) * ((int)angle / (2 * PI)); // return the angle minus the closest multiple of 2PI
    } else {
        return angle + (2 * PI) * ((int)(angle / (2 * PI)) + 1); // return the angle plus one more than multiple of 2PI
    }
}

double DtoR(double angle)
{
    return angle * PI / 180; // return the degrees in radians
}

double RtoD(double angle)
{
    return angle * 180 / PI; // return the radians in degrees
}
}