#ifndef HIT_TABLE_LIST_H
#define HIT_TABLE_LIST_H

#include "hittable.h"

#include <vector>

class hittable_list_t : public hittable_t {
public:
    void clear();
    void add(hittable_t *object);

    hit_record_t hit(ray_t ray, double ray_tmin, double ray_tmax) const final;

private:
    std::vector<hittable_t *> m_objects{};
};

#endif
