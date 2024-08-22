#include "headers\rac.hpp"
#include "headers\rac-v3.hpp"
#include "headers\rac-color.hpp"
#include "headers\rac-ppm.hpp"
#include "headers\rac-cam.hpp"

using namespace rac;
using namespace rac::static_strings;
using namespace rac::mth;
using namespace rac::gfx;
using namespace rac::img;

mut_ppm render;
mut_cam cam(ppm::WIDTH, ppm::HEIGHT);
int main()
{
    u32 pixelCt = render.PixelCount();
    for (mut_u32 i = 0; i < pixelCt; ++i)
    {
        v3 pixel_pos;
        render[i] = color::BLUE;
    }

    render.SaveToDesktop("rt_result");
    printf("\nCompleted path trace render.\n");
    return EXIT_SUCCESS;
}