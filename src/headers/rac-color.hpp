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

    class alignas(4) mut_color
    {
    private:
        static constexpr f32 NormU8(u8 x) { return (f32)x * INV_U8_MAX; }

    public:

        mut_u8 b;
        mut_u8 g;
        mut_u8 r;
        mut_u8 opacity;

        mut_color() { }
        mut_color(u8 _r, u8 _g, u8 _b, u8 _a = 255)
        {
            r = _r;
            g = _g;
            b = _b;
            opacity = _a;
        }
        mut_color(f32 _r, f32 _g, f32 _b, f32 _a)
        {
            f32 ceil_ = 255.999f;
            r = (u8)(_r * ceil_);
            g = (u8)(_g * ceil_);
            b = (u8)(_b * ceil_);
            opacity = (u8)(_a * ceil_);
        }

        INLINE u32 GetU32() const noexcept { return *(u32ptr(&b)); }
        INLINE i32 GetI32() const noexcept { return *(i32ptr(&b)); }

        INLINE f32 LinearToGamma(f32 linear_color_component) const noexcept
        {
            return powf(NormU8(linear_color_component), INV_GAMMA);
        }

        INLINE f32 GammaToLinear(f32 gamma_color_component) const noexcept
        {
            return powf(NormU8(gamma_color_component), GAMMA);
        }

        INLINE color Luminance() const noexcept
        {
            f32 ceil_ = 255.999f;

            f32 rY = LUMA_REC709_R * LinearToGamma(r);
            f32 gY = LUMA_REC709_G * LinearToGamma(g);
            f32 bY = LUMA_REC709_B * LinearToGamma(b);
            return color((u8)(rY * ceil_),
                (u8)(gY * ceil_),
                (u8)(bY * ceil_),
                opacity);
        }

        operator u32() const noexcept { return GetU32(); }
        operator i32() const noexcept { return GetI32(); }

        INLINE color_ref operator=(color_ref rhs) noexcept
        {
            b = rhs.b;
            g = rhs.g;
            r = rhs.r;
            opacity = rhs.opacity;
            return *this;
        }
    };

    typedef mut_color* mut_color_ptr;
    typedef mut_color& mut_color_ref;
    typedef const mut_color color;
    typedef const mut_color* color_ptr;
    typedef const mut_color& color_ref;
}