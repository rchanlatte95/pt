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

        INLINE v3 at(f32 t) const noexcept { return origin + t * direction; }
    };
}