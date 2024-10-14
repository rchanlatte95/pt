#pragma once
#include "rac-packedtypes.hpp"
#include "rac-rnd-xorshiftroatate.hpp"

namespace rac::rnd::distribution::uniform
{
    class mut_UniformDist;
    typedef mut_UniformDist* mut_UniformDist_ptr;
    typedef mut_UniformDist& mut_UniformDist_ref;
    typedef const mut_UniformDist UniformDist;
    typedef const mut_UniformDist* UniformDist_ptr;
    typedef const mut_UniformDist& UniformDist_ref;

    static std::vector<mut_f64> scratch;
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

            for (int i = 0; i < scratch_len; ++i)
            {
                scratch[i] = XsrRng::GetF64();
            }
        }

    public:

        MAY_INLINE static std::vector<f32> Convert(u32 len)
        {
            FillScratch((u64)len * 16ULL);

            std::vector<f32> res;
            res.reserve(len);

            return res;
        }
    };
}