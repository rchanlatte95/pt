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
    u32 CODE = ORANGE.GetU32();
    render.Fill(ORANGE);
    color c = render(0, 0);
    render.SaveToDesktop("rt_result");

    printf("Completed path trace render.");
    return EXIT_SUCCESS;
}