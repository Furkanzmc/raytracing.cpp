#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "image.h"
#include "ppm.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"
#include "hittable.h"
#include "interval.h"

#include <iostream>

int main()
{
    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    // Calculate the image height, and ensure that it's at least 1.
    const int image_width = 400;
    const int image_height = std::max(1, int(image_width / aspect_ratio));

    // Camera

    camera_t camera{.width = 2.0 * (double(image_width) / image_height),
                    .height = 2.0,
                    .focal_length = 1.0,
                    .center = point3{0, 0, 0},
                    .u = {},
                    .v = {}};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    camera.u = vec3{camera.width, 0, 0};
    camera.v = vec3{0, -camera.height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    const auto pixel_delta_u = camera.u / image_width;
    const auto pixel_delta_v = camera.v / image_height;

    // Calculate the location of the upper left pixel.
    const auto viewport_upper_left =
        camera.center - vec3(0, 0, camera.focal_length) - camera.u / 2 - camera.v / 2;
    const auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    hittable_list_t world{};
    world.add(hit::make_sphere(point3{0, -100.5, -1}, 100));

    hittable_list_t world_2{};
    world.add({.hit = [&world_2](ray_t ray, interval_t ray_inter) -> hit_record_t {
        return world_2.hit(ray, ray_inter);
    }});
    world_2.add(hit::make_sphere(point3{0, 100.5, -1}, 100));

    world.add(hit::make_sphere(point3{0, 0, -1}, 0.5));

    image_t image{image_width, image_height};
    img::init(image);

    ray_t ray{camera.center, {}};
    for (auto pos : image) {
        std::clog << "\rScanlines remaining: " << (image.height - pos.y) << ' '
                  << std::flush;

        const auto pixel_center =
            pixel00_loc + (pos.x * pixel_delta_u) + (pos.y * pixel_delta_v);
        ray.direction = pixel_center - camera.center;

        img::set_pixel(image,
                       point2i{static_cast<double>(pos.x), static_cast<double>(pos.y), 0},
                       ray::color_at(ray, world));
    }

    std::cout << image;

    std::clog << "\rDone!\n";
}
