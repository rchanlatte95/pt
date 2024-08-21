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
        mut_f32 focal_len;
        mut_f32 aspect_ratio;
        mut_v2 viewport;

        mut_v3 viewport_u;
        mut_v3 viewport_v;
        mut_v3 pixel_delta_u;
        mut_v3 pixel_delta_v;
        mut_v3 center;

        mut_cam()
        {
            focal_len = 0.0f;
            aspect_ratio = 0.0f;
            viewport = v2::ZERO;
            viewport_u = v3::ZERO;
            viewport_v = v3::ZERO;
            pixel_delta_u = v3::ZERO;
            pixel_delta_v = v3::ZERO;
            center = v3::ZERO;
        }
        mut_cam(i32 view_width, i32 view_height)
        {
            focal_len = 1.0f;
            f32 w = f32(view_width);
            f32 h = f32(view_height);

            aspect_ratio =  w / h;
            viewport = v2(2.0f, 2.0f * aspect_ratio);
            viewport_u = v3(viewport.x, 0.0f, 0.0f);
            viewport_v = v3(0.0f, -viewport.y, 0.0f);
            center = v3::ZERO;

            pixel_delta_u = viewport_u / w;
            pixel_delta_v = viewport_v / h;
        }

    };
}