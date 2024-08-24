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

static f64 RenderScene()
{
    std::chrono::steady_clock::time_point start_time = StartTimer();

    f32 invScanlineCt = 100.0f / (f32)ppm::HEIGHT;
    mut_f32 scanlinesDone = 0.0f;
    primitives::sphere test_sphere(v3(0.0f, 0.0f, -1.0f), 0.5f);
    mut_rayhit hit_info;
    for (mut_u32 y = 0; y < ppm::HEIGHT; ++y)
    {
        f32 factor = (f32)y / (f32)ppm::HEIGHT;
        for (mut_u32 x = 0; x < ppm::WIDTH; ++x)
        {
            v3 pixel_pos = cam.GetPixelPos(x, y);
            v3 ray_direction = pixel_pos - cam.center;
            ray r(cam.center, ray_direction);

            if (test_sphere.Hit(r, hit_info))
            {
                render(x, y) = Color(hit_info.normal);
            }
            else
            {
                render(x, y) = Color::Mix(Color::MISALI, Color::WHITE, factor);
            }
        }

        scanlinesDone += 1.0f;
        f32 pct_done = scanlinesDone * invScanlineCt;
        printf("\r\tPROCESSING:\t%4d / %4d scanlines (%.2f%% RENDERED).", (i32)scanlinesDone, ppm::HEIGHT, pct_done);
    }
    printf("\r\n");

    return DurationInMS(start_time);
}

int main()
{
    printf("Casting rays into scene...\r\n\r\n");
    f64 render_duration_MS = RenderScene();
    printf("\tCompleted render in %.3fms\r\n", render_duration_MS);

    printf("\r\nWriting to disk...\r\n");

    std::chrono::steady_clock::time_point write_start_time = StartTimer();
    bool save_successful = render.SaveToDesktop("rt_result");
    if (save_successful == false) { return EXIT_FAILURE; }

    printf("\tCompleted write to disk in %.3fms\r\n", DurationInMS(write_start_time));

    return EXIT_SUCCESS;
}