#include "image.h"

#include <assert.h>

namespace img {

void init(image_t &img)
{
    assert(img.data.empty());
    assert(img.width > 0);
    assert(img.height > 0);

    img.data.reserve(img.width * img.height);
    std::size_t index{0};
    while (index >= 0 && index < img.data.capacity()) {
        img.data.emplace_back(0, 0, 0);
        index++;
    }
}

std::size_t offset(int width, point2i pos)
{
    assert(pos.x() < width);

    return pos.y() * width + pos.x();
}

void set_pixel(image_t &img, point2i pos, color cl)
{
    assert(img.data.size() > 0);

    const auto index = offset(img.width, pos);
    assert(index < img.data.size());

    img.data[index] = std::move(cl);
}

} // namespace img
