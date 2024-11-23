#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

#include <vector>

struct image_t {
    int width{};
    int height{};
    std::vector<color> data{};
};

using point2i = vec3;

namespace img {
void init(image_t &img);
void set_pixel(image_t &img, const point2i &pos, color cl);
} // namespace img

#endif
