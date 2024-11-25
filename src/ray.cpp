#include "ray.h"

namespace {
bool is_in_sphere(const ray_t &ray, const point3 &center, double radius)
{
    const vec3 oc{center - ray.origin};

    const auto a = vec::dot(ray.direction, ray.direction);
    const auto b = -2.0 * vec::dot(ray.direction, oc);
    const auto c = vec::dot(oc, oc) - radius * radius;

    const auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}
} // namespace

namespace ray {
point3 position(const ray_t &ray, double t)
{
    return ray.origin + t * ray.direction;
}

color color_at(const ray_t &ray)
{
    if (is_in_sphere(ray, point3{0, 0, -1}, 0.5)) {
        return color{1, 0, 0};
    }

    const vec3 unit_direction = vec::unit_vector(ray.direction);
    const auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
}
} // namespace ray
