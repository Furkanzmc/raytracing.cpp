#ifndef INTERVAL_H
#define INTERVAL_H

#include "constants.h"

struct interval_t {
    double min{INFINITY_V};
    double max{-INFINITY_V};

    [[nodiscard]] double size() const
    {
        return max - min;
    }

    [[nodiscard]] bool contains(double x) const noexcept
    {
        return min <= x && x <= max;
    }

    [[nodiscard]] bool surrounds(double x) const noexcept
    {
        return min < x && x < max;
    }
};

namespace interval {
[[nodiscard]] interval_t empty() noexcept;
[[nodiscard]] interval_t universe() noexcept;
[[nodiscard]] double clamp(interval_t interval, double x) noexcept;
} // namespace interval

#endif
