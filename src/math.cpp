#include "mbdl/math.h"

namespace mbdl::math {
double equiv(double angle)
{
    if (angle > 0) {
        while (angle >= 2 * 3.14) {
            angle -= 2 * 3.14;
        }
    } else {
        while (angle < 0) {
            angle += 2 * 3.14;
        }
    }
    return angle;
}

double distance(double first, double second)
{
    double error = equiv(second - first);
    if (error <= 3.14) {
        return error;
    } else {
        return error - (2 * 3.14);
    }
}

double DtoR(double angle)
{
    return angle * 3.14 / 180;
}

double RtoD(double angle)
{
    return angle * 180 / 3.14;
}
}