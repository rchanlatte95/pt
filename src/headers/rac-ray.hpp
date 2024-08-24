#include "rac-mth.hpp"
#include "rac-v3.hpp"

namespace rac::mth
{
    class mut_ray;
    typedef mut_ray* mut_ray_ptr;
    typedef mut_ray& mut_ray_ref;
    typedef const mut_ray ray;
    typedef const mut_ray* ray_ptr;
    typedef const mut_ray& ray_ref;

    class mut_rayhit;
    typedef mut_rayhit* mut_rayhit_ptr;
    typedef mut_rayhit& mut_rayhit_ref;
    typedef const mut_rayhit rayhit;
    typedef const mut_rayhit* rayhit_ptr;
    typedef const mut_rayhit& rayhit_ref;

    class mut_ray
    {
    public:
        mut_v3 origin;
        mut_v3 direction;

        mut_ray()
        {
            origin = v3::ZERO;
            direction = v3::ZERO;
        }
        mut_ray(v3 origin_, v3 direction_)
        {
            origin = origin_;
            direction = direction_;
        }

        INLINE v3 At(f32 t) const noexcept { return origin + t * direction; }
    };

    class mut_rayhit
    {
    public:
        mut_v3 pos;
        mut_v3 normal;
        mut_f32 t;

        mut_rayhit()
        {
            pos = v3::ZERO;
            normal = v3::ZERO;
            t = 0.0f;
        }

        INLINE void SetNormal(ray_ref raycast, v3_ref face_normal)
        {
            const bool front_face = Dot(raycast.direction, normal) < F32_EPSILON;
            normal = front_face ? face_normal : -face_normal;
        }
    };
}