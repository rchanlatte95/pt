#include <stdio.h>

#include "headers\rac.hpp"
#include "headers\rac-tinystr.hpp"

using namespace rac;
using namespace rac::static_strings;

int main()
{
    mut_tinystr test_1 = mut_tinystr("Hello World! Hello World!", 6);
    printf(test_1);
}