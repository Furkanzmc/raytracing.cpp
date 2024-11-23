#ifndef PPM_H
#define PPM_H

#include "image.h"

#include <iostream>

std::ostream &operator<<(std::ostream &out, const image_t &img) noexcept;

#endif
