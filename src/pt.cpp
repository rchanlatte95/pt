#include "headers\rac.hpp"
#include "headers\rac-v3.hpp"
#include "headers\rac-color.hpp"
#include "headers\rac-ppm.hpp"
#include "headers\rac-camera.hpp"
#include "headers\rac-ray.hpp"
#include "headers\rac-sphere.hpp"

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
    primitives::sphere test_sphere(v3(0.0f, 0.0f, -1.0f), 1.0f);
    for (mut_u32 y = 0; y < ppm::HEIGHT; ++y)
    {
        f32 factor = (f32)y / (f32)ppm::HEIGHT;
        for (mut_u32 x = 0; x < ppm::WIDTH; ++x)
        {
            v3 pixel_pos = cam.GetPixelPos(x, y);
            v3 ray_direction = pixel_pos - cam.center;
            ray r(cam.center, ray_direction);

            color mixed = color::Mix(color::MISALI, color::WHITE, factor);
            render(x, y) = mixed;
        }

        scanlinesDone += 1.0f;
        f32 pct_done = scanlinesDone * invScanlineCt;
        printf("\r\tPROCESSING:\t%4d / %4d scanlines (%.2f%% RENDERED).          ", (i32)scanlinesDone, ppm::HEIGHT, pct_done);
    }
    printf("\r\n");

    render.SaveToDesktop("rt_result");
    return EXIT_SUCCESS;
}