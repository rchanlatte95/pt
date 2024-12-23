﻿#pragma once
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

    static f32 SIGN_HALF_LN_2PI = -HALF_LN_2PI;

    // k = -( ln(2pi)/2 )
    static f32 F32_DIST_MAX_X = 4.60303963306f - HALF_PI; // √(2k + 10 * ln(10))
    static f32 F32_DIST_MIN_X = -F32_DIST_MAX_X; // -(√(2k + 10 * ln(10)))
    class mut_UniformDist
    {
    public:

        // Get f(x) where f(x) is a non-parameterized gaussian
        // distribution function.
        INLINE static f32 Get(f32 x)
        {
            f32 half_x_sqrd = x * x * 0.5f;
            return std::expf(SIGN_HALF_LN_2PI - half_x_sqrd);
        }

        // Check if value is possibly a non-parameterized gaussian
        // distribution function.
        INLINE static bool Normal(f32 input_x, f32 input_y)
        {
            const bool x_in_range = input_x >= F32_EPSILON && input_x <= F32_DIST_MAX_X;
            return x_in_range && input_y <= Get(input_x);
        }

        // Check if value is possibly a non-parameterized gaussian
        // distribution function.
        INLINE static bool Normal(v2_ref v)
        {
            const bool x_in_range = v.x >= F32_EPSILON && v.x <= F32_DIST_MAX_X;
            return x_in_range && v.y <= Get(v.x);
        }

        MAY_INLINE static void Graph(std::vector<mut_v2>& res)
        {
            using namespace rac::rnd::XorShiftRotate;

            mut_i32 i = -1;
            while (++i < res.size())
            {
                f32 x = XsrRng::GetF32(F32_DIST_MIN_X, F32_DIST_MAX_X);
                res[i] = v2(x, UniformDist::Get(x));
            }
        }
        MAY_INLINE static void Graph01(std::vector<mut_v2>& res)
        {
            using namespace rac::rnd::XorShiftRotate;

            mut_i32 i = -1;
            f32 DELTA = 1.0f / (F32_DIST_MAX_X - F32_DIST_MIN_X);
            while (++i < res.size())
            {
                f32 x = XsrRng::GetF32(F32_DIST_MIN_X, F32_DIST_MAX_X);
                f32 x01 = (x - F32_DIST_MIN_X) * DELTA;
                res[i] = v2(x01, UniformDist::Get(x));
            }
        }
        MAY_INLINE static void Graph(std::vector<mut_v2>& res, i32 len)
        {
            using namespace rac::rnd::XorShiftRotate;

            res.reserve(len);

            mut_i32 i = -1;
            while(++i < len)
            {
                f32 x = XsrRng::GetF32(F32_DIST_MIN_X, F32_DIST_MAX_X);
                res.push_back(v2(x, UniformDist::Get(x)));
            }
        }
        MAY_INLINE static void Graph01(std::vector<mut_v2>& res, i32 len)
        {
            using namespace rac::rnd::XorShiftRotate;

            res.reserve(len);

            mut_i32 i = -1;
            f32 DELTA = 1.0f / (F32_DIST_MAX_X - F32_DIST_MIN_X);
            while (++i < len)
            {
                f32 x = XsrRng::GetF32(F32_DIST_MIN_X, F32_DIST_MAX_X);
                f32 x01 = (x - F32_DIST_MIN_X) * DELTA;
                res.push_back(v2(x01, UniformDist::Get(x)));
            }
        }

        MAY_INLINE static void Fill(std::vector<mut_v2>& res)
        {
            using namespace rac::rnd::XorShiftRotate;

            mut_i32 i = -1;
            while (++i < res.size())
            {
                f32 x = XsrRng::GetF32(F32_DIST_MIN_X, F32_DIST_MAX_X);
                f32 y_max = UniformDist::Get(x);
                res[i] = v2(x, XsrRng::GetF32(F32_EPSILON, y_max));
            }
        }
        MAY_INLINE static void Fill01(std::vector<mut_v2>& res)
        {
            using namespace rac::rnd::XorShiftRotate;

            mut_i32 i = -1;
            f32 DELTA = 1.0f / (F32_DIST_MAX_X - F32_DIST_MIN_X);
            while (++i < res.size())
            {
                f32 x = XsrRng::GetF32(F32_DIST_MIN_X, F32_DIST_MAX_X);
                f32 x01 = (x - F32_DIST_MIN_X) * DELTA;
                f32 y_max = UniformDist::Get(x);
                res[i] = v2(x01, XsrRng::GetF32(F32_EPSILON, y_max));
            }
        }
        MAY_INLINE static void Fill(std::vector<mut_v2>& res, i32 len)
        {
            using namespace rac::rnd::XorShiftRotate;

            res.reserve(len);

            mut_i32 i = -1;
            while (++i < len)
            {
                f32 x = XsrRng::GetF32(F32_DIST_MIN_X, F32_DIST_MAX_X);
                f32 y_max = UniformDist::Get(x);
                res.push_back(v2(x, XsrRng::GetF32(F32_EPSILON, y_max)));
            }
        }
        MAY_INLINE static void Fill01(std::vector<mut_v2>& res, i32 len)
        {
            using namespace rac::rnd::XorShiftRotate;

            res.reserve(len);

            mut_i32 i = -1;
            f32 DELTA = 1.0f / (F32_DIST_MAX_X - F32_DIST_MIN_X);
            while (++i < len)
            {
                f32 x = XsrRng::GetF32(F32_DIST_MIN_X, F32_DIST_MAX_X);
                f32 x01 = (x - F32_DIST_MIN_X) * DELTA;
                f32 y_max = UniformDist::Get(x);
                res.push_back(v2(x01, XsrRng::GetF32(F32_EPSILON, y_max)));
            }
        }
    };
}