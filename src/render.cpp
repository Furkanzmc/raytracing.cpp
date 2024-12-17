#include "render.h"

#include "image.h"
#include "ray.h"
#include "ppm.h"

#include <iostream>

namespace gr {
void render(hittable_t world, camera_t camera) noexcept
{
    image_t image{camera.image_width, camera.image_height};
    img::init(image);

    ray_t ray{camera.center, {}};
    for (auto pos : image) {
        std::clog << "\rScanlines remaining: " << (image.height - pos.y) << ' '
                  << std::flush;

        const auto pixel_center = camera.pixel00_loc + (pos.x * camera.pixel_delta_u) +
            (pos.y * camera.pixel_delta_v);
        ray.direction = pixel_center - camera.center;

        img::set_pixel(image,
                       point2i{static_cast<double>(pos.x), static_cast<double>(pos.y), 0},
                       ray::color_at(ray, world));
    }

    std::cout << image;

    std::clog << "\rDone!\n";
}
} // namespace gr
