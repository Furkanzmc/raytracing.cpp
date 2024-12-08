#include "ray.h"

#include "hittable_list.h"

#include "constants.h"
#include "interval.h"

namespace ray {
point3 position(ray_t ray, double t)
{
    return ray.origin + t * ray.direction;
}

color color_at(ray_t ray, const hittable_list_t &world)
{
    auto record = world.hit(ray, interval_t{.min = 0, .max = INFINITY_V});
    if (record.is_hit) {
        return 0.5 * (record.normal + color{1, 1, 1});
    }

    const vec3 unit_direction = vec::unit_vector(ray.direction);
    const auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
}
} // namespace ray
