#include "sphere.h"

#include "ray.h"
#include "hittable.h"

namespace hit {
hittable_t make_sphere(point3 center, double radius)
{
    return {.hit = [m_center = std::move(center), m_radius = radius](
                       ray_t ray, double ray_tmin, double ray_tmax) -> hit_record_t {
        const vec3 oc{m_center - ray.origin};

        const auto a = ray.direction.length_squared();
        const auto h = vec::dot(ray.direction, oc);
        const auto c = oc.length_squared() - (m_radius * m_radius);

        const auto discriminant = h * h - a * c;
        if (discriminant < 0) {
            return {};
        }

        const double sqrtd = std::sqrt(discriminant);
        // Find the nearest root that lies in the acceptable range.
        double root{(h - sqrtd) / a};
        if (root <= ray_tmin || root >= ray_tmax) {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || root >= ray_tmax) {
                return {};
            }
        }

        const auto position{ray::position(ray, root)};
        const hit_record_t record{.pos = position,
                                  .normal = (position - m_center) / m_radius,
                                  .t = root,
                                  .is_hit = true};
        const vec3 outward_normal{(record.pos - m_center) / m_radius};
        return hit_record::set_face_normal(record, ray, outward_normal);
    }};
}
} // namespace hit
