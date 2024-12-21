#ifndef PPM_H
#define PPM_H

#include "color.h"

#include <iostream>

struct image_t;

std::ostream &operator<<(std::ostream &out, const image_t &img) noexcept;

namespace ppm {
void begin(std::ostream &out, const image_t &img) noexcept;
void write_color(std::ostream &out, color pixel_color) noexcept;
} // namespace ppm

#endif
