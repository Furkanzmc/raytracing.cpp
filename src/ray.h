#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "color.h"

class hittable_list_t;

struct ray_t {
    point3 origin{};
    vec3 direction{};
};

namespace ray {
point3 position(ray_t ray, double t);
color color_at(ray_t ray, const hittable_list_t &world);
} // namespace ray

#endif
