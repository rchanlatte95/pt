#pragma once
#include "rac-packedtypes.hpp"
#include "rac-rnd-xorshiftroatate.hpp"
#include "rac-v2.hpp"

namespace rac::rnd::distribution::uniform
{
    using namespace rac::mth;

    class mut_UniformDist;
    typedef mut_UniformDist* mut_UniformDist_ptr;
    typedef mut_UniformDist& mut_UniformDist_ref;
    typedef const mut_UniformDist UniformDist;
    typedef const mut_UniformDist* UniformDist_ptr;
    typedef const mut_UniformDist& UniformDist_ref;

    static std::vector<mut_v2> scratch;
    class mut_UniformDist
    {
    private:

        MAY_INLINE static void FillScratch(u64 scratch_len)
        {
            using namespace rac::rnd::XorShiftRotate;
            if (scratch.capacity() < scratch_len)
            {
                scratch.reserve(scratch_len);
            }

            f32 X_MAX = 5.0f;
            f32 X_MIN = -X_MAX;
            for (int i = 0; i < scratch_len; ++i)
            {
                f32 x = XsrRng::GetF32(X_MIN, X_MAX);
                f32 y = XsrRng::GetF32();
                scratch[i] = v2(x, y);
            }
        }

    public:

        MAY_INLINE static std::vector<f32> Convert(u32 len)
        {
            u64 SCRATCH_CT = (u64)len * 2ULL;
            FillScratch(SCRATCH_CT);

            std::vector<f32> res;
            res.reserve(len);

            return res;
        }
    };
}