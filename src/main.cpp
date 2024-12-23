#include "ray.h"
#include "vec3.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"
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

    hittable_list_t world{};

    // Ground
    world.add(hit::make_sphere({0, -100.5, -1.0}, 100.0,
                               mat::make_lambertian({0.8, 0.8, 0.0})));

    // FIXME: The order of the objects here matter. I don't think it should...

    // Left sphere
    world.add(
        hit::make_sphere({-1.0, 0.0, -1.0}, 0.5, mat::make_metal({0.8, 0.8, 0.8}, 0.3)));

    // Right sphere
    world.add(
        hit::make_sphere({1.0, 0.0, -1.0}, 0.5, mat::make_metal({0.8, 0.6, 0.2}, 1.0)));

    // Center sphere
    world.add(
        hit::make_sphere({0.0, 0.0, -1.25}, 0.5, mat::make_lambertian({0.1, 0.2, 0.5})));

    hittable_t hit{.hit = [world = std::move(world)](auto ray, auto interval) {
        return world.hit(ray, interval);
    }};
    gr::render(hit, camera);
}
