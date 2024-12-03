#include "hittable.h"

namespace hit_record {
hit_record_t set_face_normal(hit_record_t record, ray_t ray, unit_vec3 outward_normal)
{
    record.is_front_face = vec::dot(ray.direction, outward_normal) < 0;
    record.normal = record.is_front_face ? outward_normal : -outward_normal;

    return record;
}
} // namespace hit_record
