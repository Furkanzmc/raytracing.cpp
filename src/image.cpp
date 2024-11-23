#include "image.h"

#include <assert.h>

namespace img {

std::size_t offset(const image_t &img, const point2i &pos)
{
    assert(pos.x() < img.width);
    assert(pos.y() < img.height);

    return pos.y() * img.width + pos.x();
}

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

void set_pixel(image_t &img, const point2i &pos, color cl)
{
    assert(img.data.size() > 0);

    const auto index = offset(img, pos);
    assert(index < img.data.size());

    img.data[index][0] = cl[0];
    img.data[index][1] = cl[1];
    img.data[index][2] = cl[2];
}

} // namespace img
