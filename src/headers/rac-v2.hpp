#pragma once
#include "rac.hpp"

namespace rac::mth
{
    class alignas(8) mut_v2
    {
    public:

        mut_f32 x;
        mut_f32 y;

        mut_v2()
        {
            x = 0.0f;
            y = 0.0f;
        }
        mut_v2(f32 v)
        {
            x = v;
            y = v;
        }
        mut_v2(f32 x_, f32 y_)
        {
            x = x_;
            y = y_;
        }
    };

    typedef mut_v2* mut_v2_ptr;
    typedef mut_v2& mut_v2_ref;
    typedef const mut_v2 v2;
    typedef const mut_v2* v2_ptr;
    typedef const mut_v2& v2_ref;
}