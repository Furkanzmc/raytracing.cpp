#include "ray.h"

namespace {
double hit_sphere(const ray_t &ray, const point3 &center, double radius)
{
    const vec3 oc{center - ray.origin};

    const auto a = ray.direction.length_squared();
    const auto h = vec::dot(ray.direction, oc);
    const auto c = oc.length_squared() - (radius * radius);

    const auto discriminant = h * h - a * c;
    if (discriminant < 0) {
        return -1.0;
    }

    return (h - std::sqrt(discriminant)) / a;
}
} // namespace

namespace ray {
point3 position(const ray_t &ray, double t)
{
    return ray.origin + t * ray.direction;
}

color color_at(const ray_t &ray)
{
    {
        const auto t = hit_sphere(ray, point3{0, 0, -1}, 0.5);
        if (t > 0.0) {
            const auto N = vec::unit_vector(ray::position(ray, t) - vec3{0, 0, -1});
            return 0.5 * color{N.x() + 1, N.y() + 1, N.z() + 1};
        }
    }

    const vec3 unit_direction = vec::unit_vector(ray.direction);
    const auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
}
} // namespace ray
