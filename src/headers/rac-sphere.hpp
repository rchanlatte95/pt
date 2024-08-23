#pragma once
#include "rac-v3.hpp"

namespace rac::gfx::primitives
{
    using namespace mth;

    class mut_sphere;
    typedef mut_sphere* mut_sphere_ptr;
    typedef mut_sphere& mut_sphere_ref;
    typedef const mut_sphere sphere;
    typedef const mut_sphere* sphere_ptr;
    typedef const mut_sphere& sphere_ref;
    class mut_sphere
    {
    public:
        mut_f32 radius;
        mut_v3 center;

        mut_sphere()
        {
            center = v3::ZERO;
            radius = 1.0f;
        }
        mut_sphere(v3 pos, f32 radius_ = 1.0f)
        {
            center = pos;
            radius = 1.0f;
        }
    };
}