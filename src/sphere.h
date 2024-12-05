#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

#include "vec3.h"

namespace hit {
[[nodiscard]] hittable_t make_sphere(point3 center, double radius);
}

#endif
