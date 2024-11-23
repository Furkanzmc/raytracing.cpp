#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "color.h"

struct ray_t {
    point3 origin{};
    vec3 direction{};
};

namespace ray {
point3 position(const ray_t &ray, double t);
color color_at(const ray_t &r);
} // namespace ray

#endif
