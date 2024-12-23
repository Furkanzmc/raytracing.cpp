#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
public:
    double e[3]{0, 0, 0};

    vec3()
        : e{0, 0, 0}
    {
    }

    vec3(double e0, double e1, double e2)
        : e{e0, e1, e2}
    {
    }

    [[nodiscard]] double x() const
    {
        return e[0];
    }

    [[nodiscard]] double y() const
    {
        return e[1];
    }

    [[nodiscard]] double z() const
    {
        return e[2];
    }

    [[nodiscard]] vec3 operator-() const
    {
        return vec3{-e[0], -e[1], -e[2]};
    }

    [[nodiscard]] double operator[](int i) const
    {
        return e[i];
    }

    double &operator[](int i)
    {
        return e[i];
    }

    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(double t)
    {
        return *this *= 1 / t;
    }

    [[nodiscard]] double length() const
    {
        return std::sqrt(length_squared());
    }

    [[nodiscard]] double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    [[nodiscard]] bool is_near_zero() const
    {
        constexpr auto S = 1e-8;
        return (std::fabs(e[0]) < S) && (std::fabs(e[1]) < S) && (std::fabs(e[2]) < S);
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3{u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3{u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3{u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline vec3 operator*(double t, const vec3 &v)
{
    return vec3{t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t)
{
    return (1 / t) * v;
}

namespace vec {

[[nodiscard]] double dot(vec3 u, vec3 v);
[[nodiscard]] vec3 cross(vec3 u, vec3 v);
[[nodiscard]] vec3 unit_vector(vec3 v);

[[nodiscard]] vec3 random(double min, double max);
[[nodiscard]] vec3 random();

[[nodiscard]] vec3 random_unit_vector();
[[nodiscard]] vec3 random_on_hemisphere(vec3 normal);
[[nodiscard]] vec3 reflect(vec3 v, vec3 n);

} // namespace vec

#endif
