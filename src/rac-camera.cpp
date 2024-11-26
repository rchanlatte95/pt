#include "headers/rac-camera.hpp"

namespace rac::gfx
{
    using namespace mth;

    camera::mut_camera()
    {
        focal_len = 0.0f;
        aspect_ratio = 0.0f;
        viewport = v2::ZERO;
        viewport_u = v3::ZERO;
        viewport_v = v3::ZERO;
        pixel_delta_u = v3::ZERO;
        pixel_delta_v = v3::ZERO;
        center = v3::ZERO;
        topLeft_viewport = v3::ZERO;
        pixel00_pos = v3::ZERO;
    }
    camera::mut_camera(u32 view_width, u32 view_height)
    {
        focal_len = 1.0f;
        f32 w = f32(view_width);
        f32 h = f32(view_height);

        aspect_ratio = w / h;
        viewport = v2(2.0f, 2.0f * aspect_ratio);
        viewport_u = v3(viewport.x, 0.0f, 0.0f);
        viewport_v = v3(0.0f, -viewport.y, 0.0f);
        center = v3::ZERO;

        pixel_delta_u = viewport_u / w;
        pixel_delta_v = viewport_v / h;

        v3 half_view_u = viewport_u * 0.5f;
        v3 half_view_v = viewport_v * 0.5f;

        topLeft_viewport = center - v3(0.0f, 0.0f, focal_len) - half_view_u - half_view_v;
        pixel00_pos = topLeft_viewport + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    MAY_INLINE v3 camera::GetPixelPos(i32 x, i32 y) const noexcept
    {
        return pixel00_pos + (pixel_delta_u * x) + (pixel_delta_v * y);
    }
}