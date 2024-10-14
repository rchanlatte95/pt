#pragma once
#include "rac-packedtypes.hpp"

namespace rac::rnd::distribution::uniform
{
    class mut_UniformDist;
    typedef mut_UniformDist* mut_UniformDist_ptr;
    typedef mut_UniformDist& mut_UniformDist_ref;
    typedef const mut_UniformDist UniformDist;
    typedef const mut_UniformDist* UniformDist_ptr;
    typedef const mut_UniformDist& UniformDist_ref;

    class mut_UniformDist
    {
    public:

        MAY_INLINE static std::vector<f32> Convert(u64 len, u64 X_MAX)
        {
            std::vector<f32> res;
            res.reserve(len);

            return res;
        }
    };
}