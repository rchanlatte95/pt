#include "headers\rac.hpp"
#include "headers\rac-v3.hpp"
#include "headers\rac-color.hpp"
#include "headers\rac-ppm.hpp"
#include "headers\rac-camera.hpp"
#include "headers\rac-ray.hpp"

using namespace rac;
using namespace rac::static_strings;
using namespace rac::mth;
using namespace rac::gfx;
using namespace rac::img;

mut_ppm render;
mut_camera cam(ppm::WIDTH, ppm::HEIGHT);
int main()
{
    for (mut_u32 y = 0; y < ppm::HEIGHT; ++y)
    {
        for (mut_u32 x = 0; x < ppm::WIDTH; ++x)
        {
            v3 pixel_pos = cam.GetPixelPos(x, y);
            v3 ray_direction = pixel_pos - cam.center;
            ray r(cam.center, ray_direction);

            f32 factor = 0.5f * (ray_direction.Norm().y + 1.0f);
            color mixed = color::Mix(color::WHITE, color::SKY_BLUE, factor);
            render(x, y) = mixed;
        }
    }

    render.SaveToDesktop("rt_result");
    printf("\nCompleted path trace render.\n");
    return EXIT_SUCCESS;
}