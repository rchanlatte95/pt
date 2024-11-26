#include "headers/rac-ray.hpp"

namespace rac::mth
{
    ray::mut_ray()
    {
        origin = v3::ZERO;
        direction = v3::ZERO;
    }
    ray::mut_ray(v3 origin_, v3 direction_)
    {
        origin = origin_;
        direction = direction_;
    }
    INLINE v3 ray::At(f32 t) const noexcept { return origin + t * direction; }

    rayhit::mut_rayhit()
    {
        pos = v3::ZERO;
        normal = v3::ZERO;
        t = 0.0f;
    }

    INLINE void rayhit::SetNormal(ray_ref raycast, v3_ref face_normal)
    {
        const bool front_face = Dot(raycast.direction, normal) < F32_EPSILON;
        normal = front_face ? face_normal : -face_normal;
    }
}