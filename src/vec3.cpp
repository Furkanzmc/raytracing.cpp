#include "vec3.h"

namespace vec {

double dot(vec3 u, vec3 v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

vec3 cross(vec3 u, vec3 v)
{
    return vec3{u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

} // namespace vec
