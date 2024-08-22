#pragma once
#include "rac.hpp"
#include "rac-cachestr.hpp"

namespace rac::gfx
{
    class alignas(4) mut_color;
    typedef mut_color* mut_color_ptr;
    typedef mut_color& mut_color_ref;
    typedef const mut_color color;
    typedef const mut_color* color_ptr;
    typedef const mut_color& color_ref;

    class mut_colorf;
    typedef mut_colorf* mut_colorf_ptr;
    typedef mut_colorf& mut_colorf_ref;
    typedef const mut_colorf colorf;
    typedef const mut_colorf* colorf_ptr;
    typedef const mut_colorf& colorf_ref;

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

        static color BLACK;
        static color LIGHT_GRAY;
        static color GRAY;
        static color DARK_GRAY;
        static color WHITE;

        static color RED;
        static color GREEN;
        static color BLUE;
        static color CYAN;
        static color MAGENTA;
        static color YELLOW;

        static color ORANGE;
        static color PURPLE;
        static color LAVENDER;
        static color IVORY;
        static color BURGUNDY;
        static color SKY_BLUE;
        static color OLIVE;
        static color FOREST_GREEN;
        static color OXBLOOD;
        static color OXFORD_BLUE;
        static color TURQUOISE;
        static color CHARTREUSE;
        static color SALMON;
        static color BROWN;
        static color RUST;
        static color TEAL;
        static color COBALT;
        static color EGGPLANT;
        static color PINK;
        static color KEY_LIME;

        static color LILAC;
        static color MAROON;
        static color BEIGE;
        static color TAN;
        static color PEACH;
        static color LEMON;
        static color LIME;
        static color NAVY_BLUE;

        static color GOLD;
        static color SILVER;
        static color RUBY;
        static color SAPPHIRE;
        static color EMERALD;
        static color DIAMOND;
        static color PEARL;
        static color PLATINUM;
        static color CELADON;
        static color FUCHSIA;
        static color SAFFRON;
        static color CERULEAN;
        static color INDIGO;
        static color PEWTER;
        static color VIRIDIAN;
        static color GOLDENROD;
        static color MAHOGANY;
        static color VIOLET;
        static color CINNABAR;

        mut_u8 r;
        mut_u8 g;
        mut_u8 b;
        mut_u8 opacity;

        static u8 BITS_PER_COLOR_COMPONENT = sizeof(r) * BITS_IN_BYTE;
        static u8 BITS_PER_PIXEL = BITS_PER_COLOR_COMPONENT * 4;

        mut_color()
        {
            b = 0;
            g = 0;
            r = 0;
            opacity = 255;
        }
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
        mut_color(u32 color_code)
        {
            r = (u8)(color_code >> 24);
            g = (u8)((color_code & 0x00FF0000) >> 16);
            b = (u8)((color_code & 0x0000FF00) >> 8);
            opacity = (u8)(color_code & 0x000000FF);
        }
        mut_color(i32 color_code)
        {
            r = (u8)(color_code >> 24);
            g = (u8)((color_code & 0x00FF0000) >> 16);
            b = (u8)((color_code & 0x0000FF00) >> 8);
            opacity = (u8)(color_code & 0x000000FF);
        }

        // Linearly interpolate from one color to another based on a
        MAY_INLINE static color Mix(color from, color to, f32 a)
        {
            f32 one_minus_a = 1.0f - a;
            f32 from_rf = from.r; f32 from_gf = from.b; f32 from_bf = from.b;
            f32 to_rf = to.r; f32 to_gf = to.b; f32 to_bf = to.b;
            u8 new_r = (u8)((from_rf * one_minus_a + to_rf * a) * 255.999f);
            u8 new_g = (u8)((from_gf * one_minus_a + to_gf * a) * 255.999f);
            u8 new_b = (u8)((from_bf * one_minus_a + to_bf * a) * 255.999f);
            u8 new_a = (u8)((from_bf * one_minus_a + to_bf * a) * 255.999f);
            return color(new_r, new_g, new_b, new_a);
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

        INLINE u32 GetU32() const noexcept { return *(u32ptr(&r)); }
        INLINE operator u32() const noexcept { return GetU32(); }

        INLINE i32 GetI32() const noexcept { return *(i32ptr(&r)); }
        INLINE operator i32() const noexcept { return GetI32(); }

        INLINE color_ref operator=(color_ref rhs) noexcept
        {
            b = rhs.b;
            g = rhs.g;
            r = rhs.r;
            opacity = rhs.opacity;
            return *this;
        }
        INLINE color_ref operator=(u32 color_code) noexcept
        {
            r = (u8)(color_code >> 24);
            g = (u8)((color_code & 0x00FF0000) >> 16);
            b = (u8)((color_code & 0x0000FF00) >> 8);
            opacity = (u8)(color_code & 0x000000FF);
            return *this;
        }
        INLINE color_ref operator=(i32 color_code) noexcept
        {
            opacity = (u8)(color_code >> 24);
            b = (u8)((color_code & 0x00FF0000) >> 16);
            g = (u8)((color_code & 0x0000FF00) >> 8);
            r = (u8)(color_code & 0x000000FF);
            return *this;
        }

        INLINE static_strings::mut_cachestr ToStr() const noexcept
        {
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            static_strings::mut_cachestr res;
            snprintf(res.ToCharPtr(), MAX, "(%d, %d, %d, %d)", r, g, b, opacity);
            res.Resize();
            return res;
        }
        INLINE static_strings::mut_cachestr ToPpmStr() const noexcept
        {
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            static_strings::mut_cachestr res;
            snprintf(res.ToCharPtr(), MAX, "(%d, %d, %d)", r, g, b);
            res.Resize();
            return res;
        }
    };

    class mut_colorf
    {
    public:

        mut_f32 r;
        mut_f32 g;
        mut_f32 b;
        mut_f32 opacity;

        static u8 BITS_PER_COLOR_COMPONENT = sizeof(r) * BITS_IN_BYTE;
        static u8 BITS_PER_PIXEL = BITS_PER_COLOR_COMPONENT * 4;

        mut_colorf()
        {
            r = 0.0f;
            g = 0.0f;
            b = 0.0f;
            opacity = 1.0f;
        }
        mut_colorf(u8 _r, u8 _g, u8 _b, u8 _a)
        {
            r = _r * INV_U8_MAX;
            g = _g * INV_U8_MAX;
            b = _b * INV_U8_MAX;
            opacity = _a * INV_U8_MAX;
        }
        mut_colorf(f32 _r, f32 _g, f32 _b, f32 _a = 1.0f)
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

        // Linearly interpolate from one color to another based on a
        MAY_INLINE static colorf Mix(colorf from, colorf to, f32 a)
        {
            f32 one_minus_a = 1.0f - a;
            f32 new_r = from.r * one_minus_a + to.r * a;
            f32 new_g = from.g * one_minus_a + to.g * a;
            f32 new_b = from.b * one_minus_a + to.b * a;
            f32 new_a = from.opacity * one_minus_a + to.opacity * a;
            return colorf(new_r, new_g, new_b, new_a);
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

            switch (decimal_places)
            {
            case 0:
                snprintf(res.ToCharPtr(), MAX, "(%.0f, %.0f, %.0f, %.0f)", r, g, b, opacity);
                break;
            case 1:
                snprintf(res.ToCharPtr(), MAX, "(%.1f, %.1f, %.1f, %.1f)", r, g, b, opacity);
                break;
            case 2:
                snprintf(res.ToCharPtr(), MAX, "(%.2f, %.2f, %.2f, %.2f)", r, g, b, opacity);
                break;
            case 3:
                snprintf(res.ToCharPtr(), MAX, "(%.3f, %.3f, %.3f, %.3f)", r, g, b, opacity);
                break;
            default:
                snprintf(res.ToCharPtr(), MAX, "(%.4f, %.4f, %.4f, %.4f)", r, g, b, opacity);
                break;
            }
            res.Resize();
            return res;
        }
    };

    // primary colors
    color color::BLACK = color(0x000000ff);
    color color::WHITE = color(0xffffffff);
    color color::RED =   color(0xff0000ff);
    color color::GREEN = color(0x00ff00ff);
    color color::BLUE =  color(0x0000ffff);
    color color::CYAN =  color(0x00ffffff);
    color color::MAGENTA =color(0xff00ffff);
    color color::YELLOW = color(0xffff00ff);

    // very common colors according to:
    //      https://www.color-hex.com/color-names.html ,
    //      https://simple.wikipedia.org/wiki/Colour ,
    //      and random colors I liked
    color color::DARK_GRAY = color(0x262626ff);
    color color::GRAY = color(0x7f7f7fff);
    color color::LIGHT_GRAY = color(0xd9d9d9ff);
    color color::ORANGE = color(0xffa500ff);
    color color::PURPLE = color(0xa020f0ff);
    color color::LAVENDER = color(0xb57edcff);
    color color::IVORY = color(0xfffff0ff);
    color color::BURGUNDY = color(0x800020ff);
    color color::SKY_BLUE = color(0x00ccffff);
    color color::OLIVE = color(0x808000ff);
    color color::FOREST_GREEN = color(0x228b22ff);
    color color::OXBLOOD = color(0x4a0000ff);
    color color::OXFORD_BLUE = color(0x002147ff);
    color color::TURQUOISE = color(0x40e0d0ff);
    color color::CHARTREUSE = color(0x76ee00ff);
    color color::SALMON = color(0xfa8072ff);
    color color::BROWN = color(0x654321ff);
    color color::RUST = color(0xb7410eff);
    color color::TEAL = color(0x008080ff);
    color color::COBALT = color(0x0047abff);
    color color::EGGPLANT = color(0x614051ff);
    color color::PINK = color(0xfc8eacff);
    color color::KEY_LIME = color(0xe8f48cff);
    color color::LILAC = color(0xc8a2c8ff);
    color color::MAROON = color(0xb03060ff);
    color color::BEIGE = color(0xf5f5dcff);
    color color::TAN = color(0xd2b48cff);
    color color::PEACH = color(0xffe5b4ff);
    color color::LEMON = color(0xfff700ff);
    color color::LIME = color(0x32cd32ff);
    color color::NAVY_BLUE = color(0x1974d2ff);

    // Pokemon Colors
    color color::GOLD = color(0xffd700ff);
    color color::SILVER = color(0xc0c0c0ff);
    color color::RUBY = color(0xe0115fff);
    color color::SAPPHIRE = color(0x0f52baff);
    color color::EMERALD = color(0x50c878ff);
    color color::DIAMOND = color(0xb9f2ffff);
    color color::PEARL = color(0xff5733ff);
    color color::PLATINUM = color(0xe5e4e2ff);
    color color::CELADON = color(0xace1afff);
    color color::FUCHSIA = color(0xfe4164ff);
    color color::SAFFRON = color(0xf4c430ff);
    color color::CERULEAN = color(0x007ba7ff);
    color color::INDIGO = color(0x4b0082ff);
    color color::PEWTER = color(0x8ba8b7ff);
    color color::VIRIDIAN = color(0x40826dff);
    color color::GOLDENROD = color(0xdaa520ff);
    color color::MAHOGANY = color(0xc04000ff);
    color color::VIOLET = color(0xee82eeff);
    color color::CINNABAR = color(0xe34234ff);
}