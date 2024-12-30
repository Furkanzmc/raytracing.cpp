#include "material.h"

#include "ray.h"
#include "hittable.h"
#include "utils.h"
#include "vec3.h"

#include <cassert>
#include <optional>

struct material_t::data_t {
    struct lambertian_t {
        color albedo{};
    };

    struct dielectric_t {
        double refraction_index{};
    };

    struct metal_t {
        color albedo{};
        double fuzz{};
    };

    std::optional<lambertian_t> lambertian{};
    std::optional<dielectric_t> dielectric{};
    std::optional<metal_t> metal{};
};

namespace {
material_t::scatter_response_t lambertian_scatter(const material_t &self, ray_t,
                                                  const hit_record_t &record)
{
    assert(self.data->lambertian.has_value());

    auto scatter_direction = record.normal + vec::random_unit_vector();

    // Catch degenerate scatter direction.
    if (scatter_direction.is_near_zero()) {
        scatter_direction = record.normal;
    }

    return {.scattered = {.origin = record.pos, .direction = scatter_direction},
            .attenuation = self.data->lambertian->albedo,
            .is_reflected = true};
}

material_t::scatter_response_t dielectric_scatter(const material_t &self, ray_t ray,
                                                  const hit_record_t &record)
{
    assert(self.data->dielectric.has_value());

    const auto &data = self.data->dielectric.value();

    auto reflectance = [](double cosine, double refrection_index) {
        // Schlick's approximation for reflectance
        double r0 = (1.0 - refrection_index) / (1.0 + refrection_index);
        r0 = r0 * r0;
        return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5);
    };

    const double ri =
        record.is_front_face ? (1.0 / data.refraction_index) : data.refraction_index;
    const auto unit_direction = vec::unit_vector(ray.direction);
    const double cos_theta = std::fmin(vec::dot(-unit_direction, record.normal), 1.0);
    const double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    const bool cannot_refract = ri * sin_theta > 1.0;
    vec3 direction =
        cannot_refract || reflectance(cos_theta, ri) > math::random_double(0.0, 1.0)
        ? vec::reflect(unit_direction, record.normal)
        : vec::refract(unit_direction, record.normal, ri);

    return {.scattered = {.origin = record.pos, .direction = std::move(direction)},
            .attenuation = color{1.0, 1.0, 1.0},
            .is_reflected = true};
}

material_t::scatter_response_t metal_scatter(const material_t &self, ray_t ray,
                                             const hit_record_t &record)
{
    assert(self.data->metal.has_value());

    const auto &data = self.data->metal.value();
    auto reflected = vec::reflect(ray.direction, record.normal);
    reflected = vec::unit_vector(reflected) + (data.fuzz * vec::random_unit_vector());
    ray_t scattered{.origin = record.pos, .direction = reflected};

    return {.scattered = scattered,
            .attenuation = data.albedo,
            .is_reflected = vec::dot(scattered.direction, record.normal) > 0.0};
}
} // namespace

material_t::~material_t()
{
}

material_t::scatter_response_t material_t::scatter(ray_t ray,
                                                   const hit_record_t &record) const
{
    assert(scatter_func);

    return scatter_func(*this, std::move(ray), record);
}

namespace mat {
material_t make_lambertian(color albedo)
{
    using data_t = material_t::data_t;

    auto data = std::make_shared<data_t>();
    data->lambertian = data_t::lambertian_t{.albedo = albedo};

    return {.name = "lambertian", .data = data, .scatter_func = lambertian_scatter};
}

material_t make_metal(color albedo, double fuzz)
{
    using data_t = material_t::data_t;

    auto data = std::make_shared<data_t>();
    data->metal = data_t::metal_t{.albedo = albedo, .fuzz = fuzz};

    return {.name = "metal", .data = data, .scatter_func = metal_scatter};
}

material_t make_dielectric(double refraction_index)
{
    using data_t = material_t::data_t;
    auto data = std::make_shared<data_t>();
    data->dielectric = data_t::dielectric_t{.refraction_index = refraction_index};

    return {.name = "dielectric", .data = data, .scatter_func = dielectric_scatter};
}
} // namespace mat
