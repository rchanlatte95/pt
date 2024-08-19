#include "headers\rac.hpp"
#include "headers\rac-v3.hpp"
#include "headers\rac-color.hpp"
#include "headers\rac-ppm.hpp"

using namespace rac;
using namespace rac::static_strings;
using namespace rac::mth;
using namespace rac::gfx;
using namespace rac::img;

mut_ppm render;
int main()
{
    u32 ORANGE_CODE = 0xFFA50000;
    color ORANGE(ORANGE_CODE);
    render.Fill(ORANGE);

    render.SaveToDesktop("rt_result");
    printf("\nCompleted path trace render.\n");
    return EXIT_SUCCESS;
}