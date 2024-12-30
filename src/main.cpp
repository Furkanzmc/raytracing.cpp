#include "ray.h"
#include "vec3.h"
#include "camera.h"
#include "hittable.h"
#include "render.h"
#include "material.h"

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
                    .center = {0, 0, 0},
                    .image_width = image_width,
                    .image_height = image_height,
                    .samples_per_pixel = 25};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    camera.u = vec3{camera.width, 0, 0};
    camera.v = vec3{0, -camera.height, 0};
    camera = cam::init(camera);

    // Render

    hittable_t world{};

    // Ground
    world.objects.push_back(hit::make_sphere({0, -100.5, -1.0}, 100.0,
                                             mat::make_lambertian({0.8, 0.8, 0.0})));

    // FIXME: The order of the objects here matter. I don't think it should...

    constexpr vec3 left_position{-1.0, 0.0, -1.0};

    // Left sphere
    hittable_t bubble{hit::make_sphere(left_position, 0.5, mat::make_dielectric(1.5))};
    {
        // Left bubble
        bubble.objects.push_back(
            hit::make_sphere(left_position, 0.4, mat::make_dielectric(1.0 / 1.5)));
    }
    world.objects.push_back(std::move(bubble));

    // Right sphere
    world.objects.push_back(
        hit::make_sphere({1.0, 0.0, -1.0}, 0.5, mat::make_metal({0.8, 0.6, 0.2}, 0.0)));

    // Center sphere
    world.objects.push_back(
        hit::make_sphere({0.0, 0.0, -1.2}, 0.5, mat::make_lambertian({0.1, 0.2, 0.5})));

    gr::render(std::move(world), std::move(camera));
}
