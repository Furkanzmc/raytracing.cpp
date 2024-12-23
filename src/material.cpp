#include "material.h"

#include "ray.h"
#include "hittable.h"
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
} // namespace mat
