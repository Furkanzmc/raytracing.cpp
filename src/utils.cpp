#include "utils.h"

#include <random>

namespace math {
double random_double(double min, double max)
{
    std::mt19937 gen{std::random_device{}()};

    std::uniform_real_distribution<double> distribution{min, max};
    return distribution(gen);
}
} // namespace math
