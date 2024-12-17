#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

struct camera_t {
    double width{};
    double height{};
    double focal_length{};

    vec3 center{};
    vec3 u{};
    vec3 v{};

    int image_width{};
    int image_height{};

    vec3 pixel_delta_u{};
    vec3 pixel_delta_v{};
    vec3 pixel00_loc{};
};

namespace cam {
camera_t init(camera_t camera);
}

#endif
