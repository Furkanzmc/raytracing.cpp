#include "ray.h"

#include "constants.h"
#include "interval.h"
#include "hittable.h"

namespace ray {
point3 position(ray_t ray, double t)
{
    return ray.origin + t * ray.direction;
}

color color_at(ray_t ray, int depth, const hittable_t &world)
{
    if (depth <= 0) {
        return color{0, 0, 0};
    }

    auto record = world.hit(ray, interval_t{.min = 0, .max = INFINITY_V});
    if (record.is_hit) {
        const auto direction = vec::random_on_hemisphere(record.normal);
        return 0.5 * color_at(ray_t{record.pos, direction}, depth - 1, world);
    }

    const vec3 unit_direction = vec::unit_vector(ray.direction);
    const auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
}
} // namespace ray
