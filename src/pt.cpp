#include <stdio.h>

#include "headers\rac.hpp"
#include "headers\rac-tinystr.hpp"
#include "headers\rac-v3.hpp"

using namespace rac;
using namespace rac::static_strings;

int main()
{
    rac::mth::v3 v(1.0f, 1.0f, 1.0f);
    printf("%s", v.ToStr().ToCstr());
}