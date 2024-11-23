#include "ppm.h"

#include "color.h"

namespace {
void write_color(std::ostream &out, const color &pixel_color)
{
    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = static_cast<int>(255.999 * pixel_color.x());
    int gbyte = static_cast<int>(255.999 * pixel_color.y());
    int bbyte = static_cast<int>(255.999 * pixel_color.z());

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
} // namespace

std::ostream &operator<<(std::ostream &out, const image_t &img) noexcept
{
    std::cout << "P3\n" << img.width << " " << img.height << "\n255\n";

    for (const color &cl : img.data) {
        write_color(out, cl);
    }

    return out;
}
