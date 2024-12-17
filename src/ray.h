#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "color.h"

struct hittable_t;

struct ray_t {
    point3 origin{};
    vec3 direction{};
};

namespace ray {
[[nodiscard]] point3 position(ray_t ray, double t);
[[nodiscard]] color color_at(ray_t ray, const hittable_t &world);
} // namespace ray

#endif
