#include "camera.h"

#include <cassert>

namespace cam {
camera_t init(camera_t camera)
{
    assert(camera.image_width > 0);
    assert(camera.image_height > 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    camera.pixel_delta_u = camera.u / camera.image_width;
    camera.pixel_delta_v = camera.v / camera.image_height;

    // Calculate the location of the upper left pixel.
    const auto viewport_upper_left =
        camera.center - vec3(0, 0, camera.focal_length) - camera.u / 2 - camera.v / 2;
    camera.pixel00_loc =
        viewport_upper_left + 0.5 * (camera.pixel_delta_u + camera.pixel_delta_v);

    return camera;
}
} // namespace cam
