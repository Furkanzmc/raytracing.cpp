#include "render.h"

#include "image.h"
#include "ray.h"
#include "ppm.h"
#include "utils.h"

#include <iostream>

namespace {
vec3 sample_square()
{
    return vec3{math::random_double(0, 0.5), math::random_double(0, 0.5), 0};
}

ray_t get_ray(point3 position, camera_t camera)
{
    const auto offset = sample_square();
    const auto pixel_sample = camera.pixel00_loc +
        ((position.x() + offset.x()) * camera.pixel_delta_u) +
        ((position.y() + offset.y()) * camera.pixel_delta_v);

    const auto origin{camera.center};
    const auto direction{pixel_sample - origin};

    return ray_t{origin, direction};
}
} // namespace

namespace gr {
void render(hittable_t world, camera_t camera) noexcept
{
    image_t image{camera.image_width, camera.image_height};
    img::init(image);

    for (auto pos : image) {
        std::clog << "\rScanlines remaining: " << (image.height - pos.y) << ' '
                  << std::flush;

        const point3 pos_d{
            point2i{static_cast<double>(pos.x), static_cast<double>(pos.y), 0}};

        color pixel_color{0, 0, 0};
        for (int sample = 0; sample < camera.samples_per_pixel; sample++) {
            ray_t ray{get_ray(
                point3{static_cast<double>(pos.x), static_cast<double>(pos.y), 0.0},
                camera)};
            pixel_color += ray::color_at(ray, camera.max_depth, world);
        }

        img::set_pixel(image, pos_d, camera.pixel_samples_scale * pixel_color);
    }

    std::cout << image;

    std::clog << "\rDone!\n";
}
} // namespace gr
