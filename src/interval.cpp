#include "interval.h"

#include <algorithm>

namespace interval {
interval_t empty() noexcept
{
    return {};
}

interval_t universe() noexcept
{
    return {.min = -INFINITY_V, .max = INFINITY_V};
}

double clamp(interval_t interval, double x) noexcept
{
    return std::clamp(x, interval.min, interval.max);
}
} // namespace interval
