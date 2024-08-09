#pragma once
#include "rac.hpp"

namespace rac::color
{
    // these factors are grabbed from: https://en.wikipedia.org/wiki/Luma_(video)
    // under the section: Rec. 601 luma versus Rec. 709 luma coefficients
    // I am assuming most monitors in circulation are digital HD monitors.
    f32 LUMA_REC709_R = 0.2126f;
    f32 LUMA_REC709_G = 0.7152f;
    f32 LUMA_REC709_B = 0.0722f;
    f32 GAMMA = 2.2222222f;
    f32 INV_GAMMA = 1.0f / GAMMA;

    class mut_colorf
    {
    public:

        static u8 BITS_PER_COLOR_COMPONENT = sizeof(mut_f32) * BITS_IN_BYTE;
        static u8 BITS_PER_PIXEL = BITS_PER_COLOR_COMPONENT * 4;

        mut_f32 b;
        mut_f32 g;
        mut_f32 r;
        mut_f32 opacity;

        mut_colorf() { }
        mut_colorf(u8 _r, u8 _g, u8 _b, u8 _a = 255)
        {
            r = _r * INV_U8_MAX;
            r = _g * INV_U8_MAX;
            r = _b * INV_U8_MAX;
            opacity = _a * INV_U8_MAX;
        }
        mut_colorf(f32 _r, f32 _g, f32 _b, f32 _a)
        {
            r = _r;
            g = _g;
            b = _b;
            opacity = _a;
        }

        INLINE f32 LinearToGamma(f32 linear_color_component) const noexcept
        {
            return powf(linear_color_component, INV_GAMMA);
        }

        INLINE f32 GammaToLinear(f32 gamma_color_component) const noexcept
        {
            return powf(gamma_color_component, GAMMA);
        }

        INLINE colorf Luminance() const noexcept
        {
            f32 rY = LUMA_REC709_R * LinearToGamma(r);
            f32 gY = LUMA_REC709_G * LinearToGamma(g);
            f32 bY = LUMA_REC709_B * LinearToGamma(b);
            return colorf(rY, gY, bY, opacity);
        }

        INLINE colorf_ref operator=(colorf_ref rhs) noexcept
        {
            b = rhs.b;
            g = rhs.g;
            r = rhs.r;
            opacity = rhs.opacity;
            return *this;
        }
    };

    typedef mut_colorf* mut_colorf_ptr;
    typedef mut_colorf& mut_colorf_ref;
    typedef const mut_colorf colorf;
    typedef const mut_colorf* colorf_ptr;
    typedef const mut_colorf& colorf_ref;
}