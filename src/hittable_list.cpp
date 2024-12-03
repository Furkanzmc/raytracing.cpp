#include "hittable_list.h"

void hittable_list_t::clear()
{
    m_objects.clear();
}

void hittable_list_t::add(hittable_t *object)
{
    m_objects.push_back(object);
}

hit_record_t hittable_list_t::hit(ray_t ray, double ray_tmin, double ray_tmax) const
{
    // bool hit_anything{false};
    // auto closest_so_far = ray_tmax;

    hit_record_t rec{};
    for (auto *object : m_objects) {
        auto record = object->hit(ray, ray_tmin, ray_tmax);
        if (record.is_hit) {
            // hit_anything = true;
            // closest_so_far = record.t;
            rec = std::move(record);
        }
    }

    return rec;
}
