#include <stdio.h>

#include "headers\rac.hpp"
#include "headers\rac-tinystr.hpp"
#include "headers\rac-v3.hpp"

using namespace rac;
using namespace rac::static_strings;
using namespace rac::mth;

int main()
{
    f32 test_f32_0 = -8999999.0f;
    f32 test_f32_1 = 0.1234f;
    f32 test_f32 = test_f32_0 - test_f32_1;
    v3 v(test_f32, test_f32, test_f32);
    cachestr v_str = v.ToStr();
    printf("%s", v_str.ToCstr());
}