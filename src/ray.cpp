#include "ray.h"

#include "constants.h"
#include "interval.h"
#include "hittable.h"
#include "material.h"

#include <cassert>

namespace ray {
point3 position(ray_t ray, double t)
{
    return ray.origin + t * ray.direction;
}

color color_at(ray_t ray, int depth, const hittable_t &world)
{
    if (depth <= 0) {
        return {0, 0, 0};
    }

    const auto record = hit::hit(world, ray, {.min = 0.001, .max = INFINITY_V});
    if (record.is_hit) {
        const auto response = record.material.scatter(ray, record);
        if (response.is_reflected) {
            return response.attenuation * color_at(response.scattered, depth - 1, world);
        }

        return {0, 0, 0};
    }

    const vec3 unit_direction = vec::unit_vector(ray.direction);
    const auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
}
} // namespace ray
