#ifndef RAY_MATH_H
#define RAY_MATH_H

#include "constants.h"

namespace math {
[[nodiscard]] inline double degrees_to_radians(double degrees)
{
    return degrees * PI_V / 180.0;
}
} // namespace math

#endif
