#include "camera.h"

#include "utils.h"

#include <cassert>
#include <cmath>

namespace cam {
camera_t init(camera_t camera)
{
    assert(camera.image_width > 0);
    assert(camera.image_height > 0);

    camera.pixel_samples_scale = 1.0 / camera.samples_per_pixel;
    camera.center = camera.look_from;

    const auto theta = math::degrees_to_radians(camera.vfov);
    const auto h = std::tan(theta / 2);
    camera.height = 2.0 * h * camera.focus_dist;
    camera.width =
        camera.height * (static_cast<double>(camera.image_width) / camera.image_height);

    // Calculate the vectors across the horizontal and down the vertical viewport
    // edges.
    camera.w = vec::unit_vector(camera.look_from - camera.look_at);
    camera.u = vec::unit_vector(vec::cross(camera.vup, camera.w));
    camera.v = vec::cross(camera.w, camera.u);

    const auto viewport_u = camera.width * camera.u;
    const auto viewport_v = camera.height * -camera.v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    camera.pixel_delta_u = viewport_u / camera.image_width;
    camera.pixel_delta_v = viewport_v / camera.image_height;

    // Calculate the location of the upper left pixel.
    const auto viewport_upper_left =
        camera.center - (camera.focus_dist * camera.w) - viewport_u / 2 - viewport_v / 2;
    camera.pixel00_loc =
        viewport_upper_left + 0.5 * (camera.pixel_delta_u + camera.pixel_delta_v);

    const auto defocus_radius =
        camera.focus_dist * std::tan(math::degrees_to_radians(camera.defocus_angle / 2));
    camera.defocus_disk_u = camera.u * defocus_radius;
    camera.defocus_disk_v = camera.v * defocus_radius;

    return camera;
}
} // namespace cam
