#pragma once
#include "rac-packedtypes.hpp"
#include "rac-rnd-xorshiftroatate.hpp"
#include "rac-mth.hpp"
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
    static f32 SIGN_HALF_LN_2PI = -HALF_LN_2PI;
    static f32 F32_MAX_X = 4.60303963306f; // √(2k + 10 * ln(10))
    class mut_UniformDist
    {
    private:

        MAY_INLINE static void FillF32Scratch(u64 scratch_len)
        {
            using namespace rac::rnd::XorShiftRotate;
            if (scratch.capacity() < scratch_len)
            {
                scratch.reserve(scratch_len);
            }

            f32 X_MAX = F32_MAX_X;
            f32 X_MIN = -X_MAX;
            for (int i = 0; i < scratch_len; ++i)
            {
                f32 x = XsrRng::GetF32(X_MIN, X_MAX);
                f32 y = XsrRng::GetF32();
                scratch[i] = v2(x, y);
            }
        }

        // Check if value is inside
        INLINE bool Normal_Helper_(v2_ref v) { return v.y <= Get(v.x); }

    public:

        // Get f(x) where f(x) is a non-parameterized gaussian
        // distribution function.
        INLINE f32 Get(f32 x)
        {
            f32 half_x2 = x * x * 0.5f;
            return std::expf(SIGN_HALF_LN_2PI - half_x2);
        }

        // Check if value is possibly a non-parameterized gaussian
        // distribution function.
        INLINE bool Normal(f32 input_x, f32 input_y)
        {
            const bool x_in_range = input_x >= F32_EPSILON && input_x <= F32_MAX_X;
            return x_in_range && input_y <= Get(input_x);
        }

        // Check if value is possibly a non-parameterized gaussian
        // distribution function.
        INLINE bool Normal(v2_ref v)
        {
            const bool x_in_range = v.x >= F32_EPSILON && v.x <= F32_MAX_X;
            return x_in_range && v.y <= Get(v.x);
        }

        MAY_INLINE static std::vector<f32> Convert(u32 len)
        {
            u64 SCRATCH_CT = (u64)len * 2ULL;
            FillF32Scratch(SCRATCH_CT);

            std::vector<f32> res;
            res.reserve(len);

            return res;
        }
    };
}