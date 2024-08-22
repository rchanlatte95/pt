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
    f32 invScanlineCt = 100.0f / (f32)ppm::HEIGHT;
    mut_f32 scanlinesDone = 0.0f;
    printf("Casting rays into scene...\r\n\r\n");
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

        scanlinesDone += 1.0f;
        f32 pct_done = scanlinesDone * invScanlineCt;
        printf("\r\t%4d rendered out of %4d (%.2f%% DONE).          ", (i32)scanlinesDone, ppm::HEIGHT, pct_done);
    }
    printf("\r\n");

    render.SaveToDesktop("rt_result");
    return EXIT_SUCCESS;
}