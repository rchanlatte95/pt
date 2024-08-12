#pragma once
#include "rac.hpp"

namespace rac::mth
{
    class alignas(f32) mut_v3
    {
    public:

        mut_f32 x;
        mut_f32 y;
        mut_f32 z;

        mut_v3()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
        mut_v3(f32 v)
        {
            x = v;
            y = v;
            z = v;
        }
        mut_v3(f32 x_, f32 y_)
        {
            x = x_;
            y = y_;
            z = 0.0f;
        }
        mut_v3(f32 x_, f32 y_, f32 z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }
    };

    typedef mut_v3* mut_v3_ptr;
    typedef mut_v3& mut_v3_ref;
    typedef const mut_v3 v3;
    typedef const mut_v3* v3_ptr;
    typedef const mut_v3& v3_ref;
}