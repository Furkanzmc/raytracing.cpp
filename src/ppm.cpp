#include "ppm.h"

#include "interval.h"
#include "image.h"

namespace {
double linear_to_gamma(double linear_cmp)
{
    return linear_cmp > 0 ? std::sqrt(linear_cmp) : 0;
}
} // namespace

namespace ppm {
void begin(std::ostream &out, const image_t &img) noexcept
{
    out << "P3\n" << img.width << " " << img.height << "\n255\n";
}

void write_color(std::ostream &out, color pixel_color) noexcept
{
    const double r = linear_to_gamma(pixel_color.x());
    const double g = linear_to_gamma(pixel_color.y());
    const double b = linear_to_gamma(pixel_color.z());

    auto clamp = [intr = interval_t{0.0, 0.999}](double val) {
        return interval::clamp(intr, val);
    };

    // Translate the [0,1] component values to the byte range [0,255].
    const int rbyte = static_cast<int>(256 * clamp(r));
    const int gbyte = static_cast<int>(256 * clamp(g));
    const int bbyte = static_cast<int>(256 * clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
} // namespace ppm

std::ostream &operator<<(std::ostream &out, const image_t &img) noexcept
{
    ppm::begin(out, img);

    for (const color &cl : img.data) {
        ppm::write_color(out, cl);
    }

    return out;
}
