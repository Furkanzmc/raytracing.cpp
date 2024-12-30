#include "hittable.h"

#include <cassert>

struct hittable_t::data_t {
    struct sphere_t {
        point3 center{};
        double radius{};
        material_t material{};
    };

    sphere_t sphere{};
};

namespace {
auto sphere_hit(const hittable_t &self, ray_t ray, interval_t ray_inter) -> hit_record_t
{
    using sphere_t = hittable_t::data_t::sphere_t;

    const sphere_t &sphere = self.data->sphere;

    const vec3 oc{sphere.center - ray.origin};

    const auto a = ray.direction.length_squared();
    const auto h = vec::dot(ray.direction, oc);
    const auto c = oc.length_squared() - (sphere.radius * sphere.radius);

    const auto discriminant = h * h - a * c;
    if (discriminant < 0) {
        return {};
    }

    const double sqrtd = std::sqrt(discriminant);
    // Find the nearest root that lies in the acceptable range.
    double root{(h - sqrtd) / a};
    if (!ray_inter.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_inter.surrounds(root)) {
            return {};
        }
    }

    const auto position{ray::position(ray, root)};
    hit_record_t record{.pos = position,
                        .normal = (position - sphere.center) / sphere.radius,
                        .t = root,
                        .is_hit = true,
                        .material = self.material};
    const vec3 outward_normal{(record.pos - sphere.center) / sphere.radius};
    return hit_record::set_face_normal(std::move(record), ray, outward_normal);
}
} // namespace

namespace hit {
hittable_t make_sphere(point3 center, double radius, material_t material)
{
    assert(radius > 0);

    return {.data =
                new hittable_t::data_t{.sphere = {.center = center, .radius = radius}},
            .hit = sphere_hit,
            .material = material};
}

hit_record_t hit(const hittable_t &world, ray_t ray, interval_t ray_inter)
{
#if 0
    bool hit_anything{false};
    auto closest_so_far = ray_inter.max;
#endif

    hit_record_t rec = world.hit ? world.hit(world, ray, ray_inter) : hit_record_t{};
    for (const auto &object : world.objects) {
        auto record = hit(object, ray, ray_inter);
        if (record.is_hit) {
#if 0
            hit_anything = true;
            closest_so_far = record.t;
#endif
            rec = std::move(record);
        }
    }

    return rec;
}
} // namespace hit

namespace hit_record {
hit_record_t set_face_normal(hit_record_t record, ray_t ray, unit_vec3 outward_normal)
{
    record.is_front_face = vec::dot(ray.direction, outward_normal) < 0;
    record.normal = record.is_front_face ? outward_normal : -outward_normal;

    return record;
}
} // namespace hit_record
