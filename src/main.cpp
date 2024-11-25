#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "image.h"
#include "ppm.h"
#include "camera.h"

#include <iostream>

int main()
{
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

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

    image_t image{image_width, image_height};
    img::init(image);

    ray_t ray{camera.center, {}};
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            ray.direction = pixel_center - camera.center;

            color pixel_color = ray::color_at(ray);
            img::set_pixel(image,
                           point2i{static_cast<double>(i), static_cast<double>(j), 0},
                           pixel_color);
        }
    }

    std::cout << image;

    std::clog << "\rDone.                 \n";
}
