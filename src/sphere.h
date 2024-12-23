#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

#include "vec3.h"
#include "material.h"

namespace hit {
[[nodiscard]] hittable_t make_sphere(point3 center, double radius, material_t material);
}

#endif
