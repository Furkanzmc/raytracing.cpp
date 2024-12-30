#include "utils.h"

#include <random>
#include <utility>
#include <map>

namespace math {
double random_double(double min, double max)
{
    static std::mt19937 gen{std::random_device{}()};

    using dist_pair = std::pair<double, double>;
    static std::map<dist_pair, std::uniform_real_distribution<double>> map{};

    auto foundIt = map.find(dist_pair{min, max});
    if (foundIt == map.end()) {
        foundIt = map.emplace(dist_pair{min, max},
                              std::uniform_real_distribution<double>{min, max})
                      .first;
    }

    auto &distribution = foundIt->second;
    return distribution(gen);
}
} // namespace math
