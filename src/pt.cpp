#include "headers\rac.hpp"
#include "headers\rac-v3.hpp"

using namespace rac;
using namespace rac::static_strings;
using namespace rac::mth;

int main()
{
    f32 test_f32 = -98765.1234f;
    v3 v(test_f32, test_f32, test_f32);
    cachestr v_str = v.ToStr();
    printf("%s", v_str.ToCstr());

    return EXIT_SUCCESS;
}