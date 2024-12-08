#ifndef INTERVAL_H
#define INTERVAL_H

#include "constants.h"

struct interval_t {
    double min{INFINITY_V};
    double max{-INFINITY_V};

    double size() const
    {
        return max - min;
    }

    bool contains(double x) const noexcept
    {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const noexcept
    {
        return min < x && x < max;
    }
};

namespace interval {
interval_t empty() noexcept;
interval_t universe() noexcept;
} // namespace interval

#endif
