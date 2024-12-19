#include "headers\rac.hpp"
#include "headers\rac-v3.hpp"
#include "headers\rac-color.hpp"
#include "headers\rac-ppm.hpp"
#include "headers\rac-camera.hpp"
#include "headers\rac-ray.hpp"
#include "headers\rac-sphere.hpp"
#include "headers\rac-perfstamp.hpp"
#include "headers\rac-rnd-xorshiftroatate.hpp"
#include "headers\rac-rnd-dist-uniform.hpp"

using namespace rac;
using namespace rac::static_strings;
using namespace rac::mth;
using namespace rac::gfx;
using namespace rac::img;
using namespace rac::chronology;
using namespace rac::rnd::XorShiftRotate;
using namespace rac::rnd::distribution::uniform;

mut_ppm render;

static void RenderScene(camera_ref cam)
{
    printf("Casting rays into scene...\r\n\r\n");

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
                render(x, y) = Colorf(hit_info.normal);
            }
            else
            {
                Color c = Mix(Oklab::MISALI, Oklab::WHITE, factor);
                render(x, y) = c;
            }
        }

        scanlinesDone += 1.0f;
        f32 pct_done = scanlinesDone * invScanlineCt;
        printf("\r\tPROCESSING:\t%4d / %4d scanlines (%.2f%% RENDERED).", (i32)scanlinesDone, ppm::HEIGHT, pct_done);
    }
    printf("\r\n");
}

static void Plot(std::vector<mut_v2>& data_pts, Color_ref pt_color, Color_ref background_color = Color::WHITE)
{
    render.Fill(background_color);

    const size_t pt_ct = data_pts.size();
    const f32 inv_pt_ct = 100.0f / pt_ct;
    mut_f32 pts_drawn = 0.0f;
    for (mut_u32 i = 0; i < pt_ct; ++i)
    {
        i32 center_x = (i32)(data_pts[i].x * ppm::WIDTH);
        i32 center_y = (i32)((1.0f - data_pts[i].y) * ppm::HEIGHT);

        render.DrawQuad(center_x, center_y, pt_color);

        pts_drawn += 1.0f;
        f32 pct_done = pts_drawn * inv_pt_ct;
        printf("\r\tPLOTTING:\t%4d / %4llu data points (%.2f%% PLOTTED).", (i32)pts_drawn, pt_ct, pct_done);
    }
    printf("\r\n");
}

f32 ALPHA = 1.16096404744f; //  log₄(5)
f32 INV_ALPHA = 1.0f / ALPHA; //  1 / log₄(5)
static void Pareto(std::vector<mut_v2>& data_pts)
{
    for (int i = 0; i < data_pts.size(); ++i)
    {
        v2 pt = data_pts[i];
        v2 new_pt = v2(std::powf(pt.x, -INV_ALPHA), std::powf(pt.y, -INV_ALPHA));
        data_pts[i] = new_pt;
    }
}

static bool PathTrace()
{
    mut_camera cam(ppm::WIDTH, ppm::HEIGHT);
    mut_PerfSample perf_tracker;

    perf_tracker.Start();

    RenderScene(cam);

    PerfSampleResult render_perf = perf_tracker.End();

    printf("\tCompleted render in %.3fms (%.3f MiliCycles)\r\n", render_perf.Miliseconds(), render_perf.Milicycles());
    printf("\r\nWriting to disk...\r\n");

    perf_tracker.Start();

    std::string output_path;
    FileSaveResult writeResult = render.SaveToDesktop("rt_result", output_path);
    if (writeResult.Failed())
    {
        printf("\r\n\tPath tracer result unable to save to: %s\r\n", output_path.c_str());
        return false;
    }

    PerfSampleResult write_perf = perf_tracker.End();

    f64 MB_Written = (f64)render.ByteCount() * BYTES_TO_MB;
    f64 byteRate = MB_Written / write_perf.Seconds();
    f64 cycleRate = MB_Written / write_perf.Milicycles();
    printf("\r\n\tCompleted write to disk in %.3fms (%.3f MiliCycles) | %.3f MB/s (%.3f MB/MiliCycle)\r\n", write_perf.Miliseconds(), write_perf.Milicycles(), byteRate, cycleRate);
    printf("\r\n\tPath tracer result saved to: %s\r\n", output_path.c_str());

    return true;
}

static void MixColors(Oklab_ref from, Oklab_ref to)
{
    f32 invScanlineCt = 100.0f / (f32)ppm::HEIGHT;
    mut_f32 scanlinesDone = 0.0f;
    for (mut_u32 y = 0; y < ppm::HEIGHT; ++y)
    {
        f32 factor = (f32)y / (f32)ppm::HEIGHT;
        for (mut_u32 x = 0; x < ppm::WIDTH; ++x)
        {
            Color c = Mix(from, to, factor);
            render(x, y) = c;
        }
        scanlinesDone += 1.0f;
        f32 pct_done = scanlinesDone * invScanlineCt;
        printf("\r\tPROCESSING:\t%4d / %4d scanlines (%.2f%% RENDERED).", (i32)scanlinesDone, ppm::HEIGHT, pct_done);
    }
    printf("\r\n");
}

int main()
{
    //XsrRng::Init();
    //bool successfulPathtrace = PathTrace();
    //return successfulPathtrace ? EXIT_SUCCESS : EXIT_FAILURE;



    return EXIT_SUCCESS;
}