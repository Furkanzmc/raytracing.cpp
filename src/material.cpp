#include "material.h"

#include "ray.h"
#include "hittable.h"
#include "utils.h"
#include "vec3.h"

#include <cassert>

material_t::scatter_response_t material_t::scatter(ray_t ray,
                                                   const hit_record_t &record) const
{
    assert(scatter_func);

    return scatter_func(*this, std::move(ray), record);
}

namespace mat {
material_t make_lambertian(color albedo)
{
    using response_t = material_t::scatter_response_t;

    return {.name = "lambertian",
            .scatter_func =
                [albedo = std::move(albedo)](const material_t &, ray_t,
                                             const hit_record_t &record) -> response_t {
                auto scatter_direction = record.normal + vec::random_unit_vector();

                // Catch degenerate scatter direction.
                if (scatter_direction.is_near_zero()) {
                    scatter_direction = record.normal;
                }

                return {
                    .scattered = {.origin = record.pos, .direction = scatter_direction},
                    .attenuation = albedo,
                    .is_reflected = true};
            }};
}

material_t make_metal(color albedo, double fuzz)
{
    using response_t = material_t::scatter_response_t;

    assert(fuzz <= 1.0);

    return {
        .name = "metal",
        .scatter_func = [albedo = std::move(albedo),
                         fuzz](const material_t &, ray_t ray,
                               const hit_record_t &record) -> response_t {
            auto reflected = vec::reflect(ray.direction, record.normal);
            reflected = vec::unit_vector(reflected) + (fuzz * vec::random_unit_vector());
            ray_t scattered{.origin = record.pos, .direction = reflected};

            return {.scattered = scattered,
                    .attenuation = albedo,
                    .is_reflected = vec::dot(scattered.direction, record.normal) > 0.0};
        }};
}

material_t make_dielectric(double refraction_index)
{
    using response_t = material_t::scatter_response_t;

    auto reflectance = [](double cosine, double refrection_index) {
        // Schlick's approximation for reflectance
        double r0 = (1.0 - refrection_index) / (1.0 + refrection_index);
        r0 = r0 * r0;
        return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5);
    };

    return {.name = "dielectric",
            .scatter_func = [refraction_index, reflectance = std::move(reflectance)](
                                const material_t &, ray_t ray,
                                const hit_record_t &record) -> response_t {
                (void)reflectance;
                const double ri =
                    record.is_front_face ? (1.0 / refraction_index) : refraction_index;
                const auto unit_direction = vec::unit_vector(ray.direction);
                const double cos_theta =
                    std::fmin(vec::dot(-unit_direction, record.normal), 1.0);
                const double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

                const bool cannot_refract = ri * sin_theta > 1.0;
                vec3 direction = cannot_refract ||
                        reflectance(cos_theta, ri) > math::random_double(0.0, 1.0)
                    ? vec::reflect(unit_direction, record.normal)
                    : vec::refract(unit_direction, record.normal, ri);

                return {.scattered = {.origin = record.pos,
                                      .direction = std::move(direction)},
                        .attenuation = color{1.0, 1.0, 1.0},
                        .is_reflected = true};
            }};
}
} // namespace mat
