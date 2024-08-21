#include "rac-mth.hpp"
#include "rac-v2.hpp"
#include "rac-v3.hpp"

namespace rac::gfx
{
    using namespace mth;

    class mut_cam;
    typedef mut_cam* mut_cam_ptr;
    typedef mut_cam& mut_cam_ref;
    typedef const mut_cam cam;
    typedef const mut_cam* cam_ptr;
    typedef const mut_cam& cam_ref;

    class mut_cam
    {
    public:
        mut_f32 aspect_ratio;
        mut_v3 viewport_sz;
        mut_v3 viewport_uv;
        mut_v3 center;

        mut_cam()
        {
            aspect_ratio = 0.0f;
            viewport_sz = v3::ZERO;
            viewport_uv = v3::ZERO;
            center = v3::ZERO;
        }

    };
}