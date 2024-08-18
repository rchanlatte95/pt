#pragma once
#include "rac.hpp"
#include "rac-cachestr.hpp"

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
    public:

        mut_u8 b;
        mut_u8 g;
        mut_u8 r;
        mut_u8 opacity;

        static u8 BITS_PER_COLOR_COMPONENT = sizeof(r) * BITS_IN_BYTE;
        static u8 BITS_PER_PIXEL = BITS_PER_COLOR_COMPONENT * 4;

        mut_color() { }
        mut_color(u8 _r, u8 _g, u8 _b, u8 _a = 255)
        {
            b = _b;
            g = _g;
            r = _r;
            opacity = _a;
        }
        mut_color(f32 _r, f32 _g, f32 _b, f32 _a)
        {
            b = (u8)(_b * 255.999f);
            g = (u8)(_g * 255.999f);
            r = (u8)(_r * 255.999f);
            opacity = (u8)(_a * 255.999f);
        }
        mut_color(colorf_ref c)
        {
            b = (u8)(c.b * 255.999f);
            g = (u8)(c.g * 255.999f);
            r = (u8)(c.r * 255.999f);
            opacity = (u8)(c.opacity * 255.999f);
        }

        INLINE f32 LinearToGamma(f32 linear_color_component) const noexcept
        {
            return powf((f32)linear_color_component * INV_U8_MAX, INV_GAMMA);
        }
        INLINE f32 GammaToLinear(f32 gamma_color_component) const noexcept
        {
            return powf((f32)gamma_color_component * INV_U8_MAX, GAMMA);
        }

        INLINE color Luminance() const noexcept
        {
            f32 rY = LUMA_REC709_R * LinearToGamma(r);
            f32 gY = LUMA_REC709_G * LinearToGamma(g);
            f32 bY = LUMA_REC709_B * LinearToGamma(b);
            u8 new_r = (u8)(rY * 255.999f);
            u8 new_g = (u8)(gY * 255.999f);
            u8 new_b = (u8)(bY * 255.999f);
            return color(new_r, new_g, new_b, opacity);
        }

        INLINE u32 GetU32() const noexcept { return *(u32ptr(&opacity)); }
        INLINE operator u32() const noexcept { return GetU32(); }

        INLINE i32 GetI32() const noexcept { return *(i32ptr(&opacity)); }
        INLINE operator i32() const noexcept { return GetI32(); }

        INLINE colorf ToColorf() const noexcept { return colorf(*this); }
        INLINE operator colorf() const noexcept { return ToColorf(); }

        INLINE color_ref operator=(color_ref rhs) noexcept
        {
            b = rhs.b;
            g = rhs.g;
            r = rhs.r;
            opacity = rhs.opacity;
            return *this;
        }
        INLINE color_ref operator=(colorf_ref rhs) noexcept
        {
            b = rhs.b;
            g = rhs.g;
            r = rhs.r;
            opacity = rhs.opacity;
            return *this;
        }

        INLINE static_strings::mut_cachestr ToStr() const noexcept
        {
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            static_strings::mut_cachestr res;
            snprintf(res.ToCharPtr(), MAX, "(%3d, %3d, %3d, %3d)", r, g, b, opacity);
            res.Resize();
            return res;
        }

        INLINE static_strings::mut_cachestr ToPpmStr() const noexcept
        {
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            static_strings::mut_cachestr res;
            snprintf(res.ToCharPtr(), MAX, "(%3d, %3d, %3d)", r, g, b);
            res.Resize();
            return res;
        }
    };

    typedef mut_color* mut_color_ptr;
    typedef mut_color& mut_color_ref;
    typedef const mut_color color;
    typedef const mut_color* color_ptr;
    typedef const mut_color& color_ref;

    class mut_colorf
    {
    public:

        mut_f32 r;
        mut_f32 g;
        mut_f32 b;
        mut_f32 opacity;

        static u8 BITS_PER_COLOR_COMPONENT = sizeof(r) * BITS_IN_BYTE;
        static u8 BITS_PER_PIXEL = BITS_PER_COLOR_COMPONENT * 4;

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
        mut_colorf(color_ref c)
        {
            r = c.r * INV_U8_MAX;
            g = c.g * INV_U8_MAX;
            b = c.b * INV_U8_MAX;
            opacity = c.opacity * INV_U8_MAX;
        }

        INLINE f32 LinearToGamma(f32 linear_color_component) const noexcept
        {
            return powf(linear_color_component, INV_GAMMA);
        }
        INLINE f32 GammaToLinear(f32 gamma_color_component) const noexcept
        {
            return powf(gamma_color_component, GAMMA);
        }
        INLINE colorf ToLinear() const noexcept
        {
            return colorf(LinearToGamma(r), LinearToGamma(g), LinearToGamma(b), opacity);
        }
        INLINE colorf ToGamma() const noexcept
        {
            return colorf(GammaToLinear(r), GammaToLinear(g), GammaToLinear(b), opacity);
        }

        INLINE colorf Luminance() const noexcept
        {
            f32 rY = LUMA_REC709_R * LinearToGamma(r);
            f32 gY = LUMA_REC709_G * LinearToGamma(g);
            f32 bY = LUMA_REC709_B * LinearToGamma(b);
            return colorf(rY, gY, bY, opacity);
        }

        INLINE color ToColor() const noexcept { return color(*this); }
        INLINE operator color() const noexcept { return ToColor(); }

        INLINE colorf_ref operator=(colorf_ref rhs) noexcept
        {
            b = rhs.b;
            g = rhs.g;
            r = rhs.r;
            opacity = rhs.opacity;
            return *this;
        }

        mut_f32 operator [] (i32 i) const { return *(&r + i); }
        mut_f32ref operator [] (i32 i) { return *(&r + i); }

        INLINE static_strings::mut_cachestr ToStr(u32 decimal_places = 4) const noexcept
        {
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            static_strings::mut_cachestr res;
            bool use_exp = (r >= MAX_F32_FOR_FULL_REP || r <= MIN_F32_FOR_FULL_REP) ||
                            (g >= MAX_F32_FOR_FULL_REP || g <= MIN_F32_FOR_FULL_REP) ||
                            (b >= MAX_F32_FOR_FULL_REP || b <= MIN_F32_FOR_FULL_REP) ||
                            (opacity >= MAX_F32_FOR_FULL_REP || opacity <= MIN_F32_FOR_FULL_REP);

            switch (decimal_places)
            {
            case 0:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.0e, %.0e, %.0e)" : "(%.0f, %.0f, %.0f)", r, g, b, opacity);
                break;
            case 1:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.1e, %.1e, %.1e)" : "(%.1f, %.1f, %.1f)", r, g, b, opacity);
                break;
            case 2:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.2e, %.2e, %.2e)" : "(%.2f, %.2f, %.2f)", r, g, b, opacity);
                break;
            case 3:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.3e, %.3e, %.3e)" : "(%.3f, %.3f, %.3f)", r, g, b, opacity);
                break;
            default:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.4e, %.4e, %.4e)" : "(%.4f, %.4f, %.4f)", r, g, b, opacity);
                break;
            }
            res.Resize();
            return res;
        }
    };

    typedef mut_colorf* mut_colorf_ptr;
    typedef mut_colorf& mut_colorf_ref;
    typedef const mut_colorf colorf;
    typedef const mut_colorf* colorf_ptr;
    typedef const mut_colorf& colorf_ref;
}