#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "color.h"

#include <memory>
#include <string>

struct hit_record_t;

struct material_t {
    struct scatter_response_t {
        ray_t scattered{};
        color attenuation{};
        bool is_reflected{false};
    };

    using scatter_function = scatter_response_t (*)(const material_t &, ray_t,
                                                    const hit_record_t &);

    std::string name{};

    struct data_t;
    std::shared_ptr<data_t> data{nullptr};
    scatter_function scatter_func{};

    ~material_t();
    [[nodiscard]] scatter_response_t scatter(ray_t ray, const hit_record_t &record) const;
};

namespace mat {
[[nodiscard]] material_t make_lambertian(color albedo);
[[nodiscard]] material_t make_metal(color albedo, double fuzz);
[[nodiscard]] material_t make_dielectric(double refraction_index);
} // namespace mat

#endif
