#include <stdio.h>

#include "headers\rac.hpp"
#include "headers\rac-tinystr.hpp"

using namespace rac;
using namespace rac::static_strings;

int main()
{
    mut_tinystr test_1 = mut_tinystr("Hello");
    test_1 += ' ';
    test_1 += 'W';
    test_1 += 'o';
    test_1 += 'r';
    test_1 += 'l';
    test_1 += 'd';
    test_1 += '!';
    printf("%s", test_1.ToCstr());
}