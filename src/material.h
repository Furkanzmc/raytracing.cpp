#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "color.h"

#include <functional>
#include <string>

struct hit_record_t;

struct material_t {
    struct scatter_response_t {
        ray_t scattered{};
        color attenuation{};
        bool is_reflected{false};
    };

    using scatter_function = std::function<scatter_response_t(const material_t &, ray_t,
                                                              const hit_record_t &)>;

    std::string name{};
    scatter_function scatter_func{};

    scatter_response_t scatter(ray_t ray, const hit_record_t &record) const;
};

namespace mat {
material_t make_lambertian(color albedo);
material_t make_metal(color albedo, double fuzz);
} // namespace mat

#endif
