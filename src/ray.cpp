#include "ray.h"

namespace ray {
point3 position(const ray_t &ray, double t)
{
    return ray.origin + t * ray.direction;
}

color color_at(const ray_t &r)
{
    const vec3 unit_direction = vec::unit_vector(r.direction);
    const auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
}
} // namespace ray
