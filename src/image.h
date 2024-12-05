#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

#include <vector>

struct image_pix_iterator_t {
    using iterator_category = std::forward_iterator_tag;
    using value_type = struct position {
        int x{};
        int y{};
    };
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type *;
    using reference = const value_type &;

    image_pix_iterator_t(int image_width, int image_height)
        : image_width{image_width}
        , image_height{image_height}
    {
    }

    image_pix_iterator_t &operator++()
    {
        ++current_x;
        if (current_x >= image_width) {
            current_x = 0;
            ++current_y;
        }

        return *this;
    }

    [[nodiscard]] image_pix_iterator_t operator++(int)
    {
        image_pix_iterator_t temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(image_pix_iterator_t other) const
    {
        return image_width == other.image_width && image_height == other.image_height &&
            current_x == other.current_x && current_y == other.current_y;
    }

    bool operator!=(image_pix_iterator_t other) const
    {
        return !(*this == other);
    }

    [[nodiscard]] value_type operator*() const
    {
        return {current_x, current_y};
    }

    [[nodiscard]] image_pix_iterator_t advance(int n)
    {
        image_pix_iterator_t it = *this;
        it.current_x += n % image_width;
        it.current_y += n / image_width;
        return it;
    }

private:
    int image_width{};
    int image_height{};
    int current_x{};
    int current_y{};
};

struct image_t {
    int width{};
    int height{};
    std::vector<color> data{};

    [[nodiscard]] image_pix_iterator_t begin() const noexcept
    {
        return image_pix_iterator_t{width, height};
    }

    [[nodiscard]] image_pix_iterator_t end() const noexcept
    {
        return image_pix_iterator_t(width, height).advance(width * height - 1);
    }
};

using point2i = vec3;

namespace img {
void init(image_t &img);
[[nodiscard]] std::size_t offset(int width, point2i pos);
void set_pixel(image_t &img, point2i pos, color cl);
} // namespace img

#endif
