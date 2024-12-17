#ifndef RENDER_H
#define RENDER_H

#include "hittable.h"
#include "camera.h"

namespace gr {
void render(hittable_t world, camera_t camera) noexcept;
}

#endif
