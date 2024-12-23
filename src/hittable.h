#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"

#include "ray.h"
#include "interval.h"
#include "material.h"

struct hit_record_t {
    point3 pos{};
    vec3 normal{};
    double t{};
    bool is_front_face{false};
    bool is_hit{false};
    material_t material{};
};

struct hittable_t {
    using hit_func = std::function<hit_record_t(ray_t ray, interval_t ray_inter)>;

    hit_func hit{};
    material_t material{};
};

namespace hit_record {
using unit_vec3 = vec3;
[[nodiscard]] hit_record_t set_face_normal(hit_record_t record, ray_t ray,
                                           unit_vec3 outward_normal);
} // namespace hit_record

#endif
