#include <stdio.h>

#include "headers\rac.hpp"
#include "headers\rac-tinystr.hpp"

using namespace rac;
using namespace rac::static_strings;

int main()
{
    std::string str = "test";
    mut_tinystr test_1 = mut_tinystr("Hello");
    test_1 = str;
    printf("%s", test_1.ToCstr());
}