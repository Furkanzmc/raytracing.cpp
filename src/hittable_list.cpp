#include "hittable_list.h"

void hittable_list_t::clear()
{
    m_objects.clear();
}

void hittable_list_t::add(hittable_t object)
{
    m_objects.push_back(std::move(object));
}

hit_record_t hittable_list_t::hit(ray_t ray, interval_t ray_inter) const
{
#if 0
    bool hit_anything{false};
    auto closest_so_far = ray_inter.max;
#endif

    hit_record_t rec{};
    for (auto object : m_objects) {
        auto record = object.hit(ray, ray_inter);
        if (record.is_hit) {
#if 0
            hit_anything = true;
            closest_so_far = record.t;
#endif
            rec = std::move(record);
        }
    }

    return rec;
}
