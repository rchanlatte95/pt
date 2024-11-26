#pragma once
#include "rac-v3.hpp"

namespace rac::gfx
{
    using namespace mth;

    class mut_camera;
    typedef mut_camera* mut_camera_ptr;
    typedef mut_camera& mut_camera_ref;
    typedef const mut_camera camera;
    typedef const mut_camera* camera_ptr;
    typedef const mut_camera& camera_ref;

    class mut_camera
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

        mut_v3 topLeft_viewport;
        mut_v3 pixel00_pos;

        mut_camera();
        mut_camera(u32 view_width, u32 view_height);

        MAY_INLINE v3 GetPixelPos(i32 x, i32 y) const noexcept;
    };
}