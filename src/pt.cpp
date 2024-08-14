#include <stdio.h>

#include "headers\rac.hpp"
#include "headers\rac-tinystr.hpp"

using namespace rac;
using namespace rac::static_strings;

int main()
{
    mut_tinystr test_hello = mut_tinystr("Hello");
    mut_tinystr test_world = mut_tinystr(" World!\n");
    tinystr res = test_hello + test_world;
    printf(res);
}