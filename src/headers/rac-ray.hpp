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
            origin = v3(0.0f);
            direction = v3(0.0f);
        }
        mut_ray(v3 v)
        {
            x = v;
            y = v;
            z = v;
        }


        INLINE static_strings::mut_cachestr ToStr(u32 decimal_places = 4) const noexcept
        {
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            static_strings::mut_cachestr res;
            bool use_exp = Between(x, MAX_F32_FOR_FULL_REP) ||
                            Between(y, MAX_F32_FOR_FULL_REP) ||
                            Between(z, MAX_F32_FOR_FULL_REP);

            switch (decimal_places)
            {
            case 0:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.0e, %.0e, %.0e)" : "(%.0f, %.0f, %.0f)", x, y, z);
                break;
            case 1:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.1e, %.1e, %.1e)" : "(%.1f, %.1f, %.1f)", x, y, z);
                break;
            case 2:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.2e, %.2e, %.2e)" : "(%.2f, %.2f, %.2f)", x, y, z);
                break;
            case 3:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.3e, %.3e, %.3e)" : "(%.3f, %.3f, %.3f)", x, y, z);
                break;
            default:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.4e, %.4e, %.4e)" : "(%.4f, %.4f, %.4f)", x, y, z);
                break;
            }
            res.Resize();
            return res;
        }
    };
}