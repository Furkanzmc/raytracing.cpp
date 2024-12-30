#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"
#include "interval.h"
#include "material.h"

#include <vector>

struct hit_record_t {
    point3 pos{};
    vec3 normal{};
    double t{};
    bool is_front_face{false};
    bool is_hit{false};
    material_t material{};
};

struct hittable_t {
    using hit_func = hit_record_t (*)(const hittable_t &self, ray_t ray,
                                      interval_t ray_inter);

    struct data_t;

    data_t *data{nullptr};
    hit_func hit{nullptr};
    material_t material{};
    std::vector<hittable_t> objects{};
};

namespace hit {
[[nodiscard]] hittable_t make_sphere(point3 center, double radius, material_t material);
[[nodiscard]] hit_record_t hit(const hittable_t &world, ray_t ray, interval_t ray_inter);
} // namespace hit

namespace hit_record {
using unit_vec3 = vec3;
[[nodiscard]] hit_record_t set_face_normal(hit_record_t record, ray_t ray,
                                           unit_vec3 outward_normal);
} // namespace hit_record

#endif
