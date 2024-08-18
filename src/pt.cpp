#include "headers\rac.hpp"
#include "headers\rac-v3.hpp"
#include "headers\rac-color.hpp"
#include "headers\rac-ppm.hpp"

using namespace rac;
using namespace rac::static_strings;
using namespace rac::mth;
using namespace rac::color;
using namespace rac::img;

static mut_ppm render;
int main()
{
    render.SaveToDesktop("rt_result");

    printf("Completed path trace render.");
    return EXIT_SUCCESS;
}