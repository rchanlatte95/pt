#include <stdio.h>

#include "headers\rac.hpp"
#include "headers\rac-tinystr.hpp"

using namespace rac;
using namespace rac::static_strings;

int main()
{
    mut_tinystr test_1 = 'H' + mut_tinystr("ello") + ' ' + "World!";
    printf("%s", test_1.ToCstr());
}