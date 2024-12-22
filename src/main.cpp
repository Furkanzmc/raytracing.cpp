#include "ray.h"
#include "vec3.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"
#include "hittable.h"
#include "interval.h"
#include "render.h"

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
                    .image_width = image_width,
                    .image_height = image_height,
                    .samples_per_pixel = 5};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    camera.u = vec3{camera.width, 0, 0};
    camera.v = vec3{0, -camera.height, 0};
    camera = cam::init(camera);

    // Render

    hittable_list_t world{};
    world.add(hit::make_sphere(point3{0, -100.5, -1}, 100));

    hittable_list_t world_2{};
    world.add({.hit = [&world_2](ray_t ray, interval_t ray_inter) -> hit_record_t {
        return world_2.hit(ray, ray_inter);
    }});
    // world_2.add(hit::make_sphere(point3{0, 100.5, -1}, 100));

    world.add(hit::make_sphere(point3{0, 0, -1}, 0.5));

    hittable_t hit{.hit = [&world](ray_t ray, interval_t inter) {
        return world.hit(ray, inter);
    }};
    gr::render(hit, camera);
}
