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
};

#endif
