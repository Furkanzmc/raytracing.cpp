#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"

#include "ray.h"

struct hit_record_t {
    point3 pos{};
    vec3 normal{};
    double t{};
    bool is_front_face{false};
    bool is_hit{false};
};

class hittable_t {
public:
    virtual ~hittable_t() = default;

    virtual hit_record_t hit(ray_t ray, double ray_tmin, double ray_tmax) const = 0;
};

namespace hit_record {
using unit_vec3 = vec3;
hit_record_t set_face_normal(hit_record_t record, ray_t ray, unit_vec3 outward_normal);
} // namespace hit_record

#endif
