#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

#include "vec3.h"

class sphere_t : public hittable_t {
public:
    sphere_t(point3 center, double radius);
    ~sphere_t() = default;

    hit_record_t hit(ray_t ray, double ray_tmin, double ray_tmax) const final;

private:
    point3 m_center{};
    double m_radius{};
};

#endif
