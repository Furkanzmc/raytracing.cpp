#include "ray.h"
#include "vec3.h"
#include "camera.h"
#include "hittable.h"
#include "render.h"
#include "utils.h"
#include "material.h"

namespace {
hittable_t create_final_scene()
{
    hittable_t world =
        hit::make_sphere({0, -1000, 0}, 1000, mat::make_lambertian({0.5, 0.5, 0.5}));

    constexpr int count{11};
    for (int a = count * -1; a < count; a++) {
        for (int b = count * -1; b < count; b++) {
            const auto choose_mat = math::random_double(0, 1);
            const point3 center{a + 0.9 * math::random_double(0, 1), 0.2,
                                b + 0.9 * math::random_double(0, 1)};

            if ((center - point3{4, 0.2, 0}).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // Diffuse
                    auto albedo = vec::random() * vec::random();
                    world.objects.push_back(hit::make_sphere(
                        center, 0.2, mat::make_lambertian(std::move(albedo))));
                }
                else if (choose_mat < 0.95) {
                    // Metal
                    world.objects.push_back(
                        hit::make_sphere(center, 0.2,
                                         mat::make_metal(vec::random(0.5, 1),
                                                         math::random_double(0, 0.5))));
                }
                else {
                    // Glass
                    world.objects.push_back(
                        hit::make_sphere(center, 0.2, mat::make_dielectric(1.5)));
                }
            }
        }
    }

    world.objects.push_back(
        hit::make_sphere({-4, 1, 0}, 1.0, mat::make_lambertian({0.4, 0.2, 0.1})));

    world.objects.push_back(hit::make_sphere({0, 1, 0}, 1.0, mat::make_dielectric(1.5)));

    world.objects.push_back(
        hit::make_sphere({4, 1, 0}, 1.0, mat::make_metal({0.7, 0.6, 0.5}, 0.0)));

    return world;
}
} // namespace

int main()
{
    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    // Calculate the image height, and ensure that it's at least 1.
    const int image_width = 500;
    const int image_height = std::max(1, int(image_width / aspect_ratio));

    // Camera

    camera_t camera = cam::init({.image_width = image_width,
                                 .image_height = image_height,
                                 .samples_per_pixel = 50,
                                 .max_depth = 10,
                                 .vfov = 25,
                                 .look_from = {13, 2, 3},
                                 .look_at = {0, 0, 0},
                                 .vup = {0, 1, 0},
                                 .defocus_angle = 0.6,
                                 .focus_dist = 10});

    // Render

    gr::render(create_final_scene(), std::move(camera));
}
