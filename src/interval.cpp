#include "interval.h"

namespace interval {
interval_t empty() noexcept
{
    return {};
}

interval_t universe() noexcept
{
    return {.min = -INFINITY_V, .max = INFINITY_V};
}
} // namespace interval
