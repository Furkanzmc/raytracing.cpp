#include "vec3.h"

#include "utils.h"

#include <cmath>

namespace vec {

double dot(vec3 u, vec3 v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

vec3 cross(vec3 u, vec3 v)
{
    return vec3{u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

vec3 random(double min, double max)
{
    return vec3{math::random_double(min, max), math::random_double(min, max),
                math::random_double(min, max)};
}

vec3 random()
{
    return random(0, 1);
}

vec3 random_unit_vector()
{
    constexpr double EPSILON{1e-160};

    while (true) {
        const auto p = random(-1, 1);
        const auto lensq = p.length_squared();
        if (lensq > EPSILON && lensq <= 1) {
            return p / std::sqrt(lensq);
        }
    }
}

vec3 random_on_hemisphere(vec3 normal)
{
    const auto on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0) {
        return on_unit_sphere;
    }

    return on_unit_sphere * -1;
}

vec3 reflect(vec3 v, vec3 n)
{
    return v - 2 * dot(v, n) * n;
}

vec3 refract(vec3 uv, vec3 n, double etai_over_etat)
{
    const auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    const auto r_out_perp = etai_over_etat * (uv + cos_theta * n);
    const auto r_out_parallel =
        -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;

    return r_out_perp + r_out_parallel;
}

} // namespace vec
