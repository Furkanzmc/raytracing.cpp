#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

struct camera_t {
    double width{};
    double height{};
    vec3 center{0.0, 0.0, 0.0};

    vec3 u{};
    vec3 v{};
    vec3 w{};

    int image_width{};
    int image_height{};

    vec3 pixel_delta_u{};
    vec3 pixel_delta_v{};
    vec3 pixel00_loc{};

    int samples_per_pixel{10};

    // Color scale factor for a sum of pixel samples.
    double pixel_samples_scale{};

    int max_depth{20};
    double vfov{90};

    point3 look_from{0, 0, 0};
    point3 look_at{0, 0, -1};
    vec3 vup{0, 1, 0};

    double defocus_angle{10};
    double focus_dist{3.4};

    vec3 defocus_disk_u{};
    vec3 defocus_disk_v{};
};

namespace cam {
camera_t init(camera_t camera);
}

#endif
