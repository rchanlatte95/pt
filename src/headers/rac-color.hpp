#pragma once
#include "rac-v3.hpp"

namespace rac::gfx
{
    using namespace mth;

    class alignas(4) mut_Color;
    typedef mut_Color* mut_Color_ptr;
    typedef mut_Color& mut_Color_ref;
    typedef const mut_Color Color;
    typedef const mut_Color* Color_ptr;
    typedef const mut_Color& Color_ref;

    class alignas(4) mut_Colorf;
    typedef mut_Colorf* mut_Colorf_ptr;
    typedef mut_Colorf& mut_Colorf_ref;
    typedef const mut_Colorf Colorf;
    typedef const mut_Colorf* Colorf_ptr;
    typedef const mut_Colorf& Colorf_ref;

    class alignas(4) mut_Oklab;
    typedef mut_Oklab* mut_Oklab_ptr;
    typedef mut_Oklab& mut_Oklab_ref;
    typedef const mut_Oklab Oklab;
    typedef const mut_Oklab* Oklab_ptr;
    typedef const mut_Oklab& Oklab_ref;

    // these factors are grabbed from: https://en.wikipedia.org/wiki/Luma_(video)
    // under the section: Rec. 601 luma versus Rec. 709 luma coefficients
    // I am assuming most monitors in circulation are digital HD monitors.
    f32 LUMA_REC709_R = 0.2126f;
    f32 LUMA_REC709_G = 0.7152f;
    f32 LUMA_REC709_B = 0.0722f;
    f32 GAMMA = 2.4f;
    f32 INV_GAMMA = 1.0f / GAMMA;

    f32 GAMMA_CORRECTION_FACTOR = 1.055f;
    f32 INV_GAMMA_CORRECTION_FACTOR = 1.0f / GAMMA_CORRECTION_FACTOR;
    f32 SMALL_GAMMA_CORRECTION_FACTOR = 12.92f;
    f32 INV_SMALL_GAMMA_CORRECTION_FACTOR = 1.0f / SMALL_GAMMA_CORRECTION_FACTOR;

    // https://bottosson.github.io/posts/colorwrong/#what-can-we-do%3F
    INLINE f32 LinearToGamma(f32 linear_color_component) noexcept
    {
        if (linear_color_component >= 0.0031308f)
        {
            return GAMMA_CORRECTION_FACTOR * powf(linear_color_component, INV_GAMMA) - 0.055f;
        }
        else
        {
            return SMALL_GAMMA_CORRECTION_FACTOR * linear_color_component;
        }
    }
    INLINE f32 GammaToLinear(f32 gamma_color_component) noexcept
    {
        if (gamma_color_component >= 0.04045f)
        {
            return powf((gamma_color_component + 0.055) * INV_GAMMA_CORRECTION_FACTOR, GAMMA);
        }
        else
        {
            return gamma_color_component * INV_SMALL_GAMMA_CORRECTION_FACTOR;
        }
    }

    class alignas(4) mut_Color
    {
    public:

        static Color BLACK;
        static Color LIGHT_GRAY;
        static Color GRAY;
        static Color DARK_GRAY;
        static Color WHITE;

        static Color RED;
        static Color GREEN;
        static Color BLUE;
        static Color CYAN;
        static Color MAGENTA;
        static Color YELLOW;

        static Color ORANGE;
        static Color PURPLE;
        static Color LAVENDER;
        static Color IVORY;
        static Color BURGUNDY;
        static Color SKY_BLUE;
        static Color OLIVE;
        static Color FOREST_GREEN;
        static Color OXBLOOD;
        static Color OXFORD_BLUE;
        static Color TURQUOISE;
        static Color CHARTREUSE;
        static Color SALMON;
        static Color BROWN;
        static Color RUST;
        static Color TEAL;
        static Color COBALT;
        static Color EGGPLANT;
        static Color PINK;
        static Color KEY_LIME;

        static Color LILAC;
        static Color MAROON;
        static Color BEIGE;
        static Color TAN;
        static Color PEACH;
        static Color LEMON;
        static Color LIME;
        static Color NAVY_BLUE;

        // https://colornames.org/color/80c0ff
        static Color MISALI;

        static Color GOLD;
        static Color SILVER;
        static Color RUBY;
        static Color SAPPHIRE;
        static Color EMERALD;
        static Color DIAMOND;
        static Color PEARL;
        static Color PLATINUM;
        static Color CELADON;
        static Color FUCHSIA;
        static Color SAFFRON;
        static Color CERULEAN;
        static Color INDIGO;
        static Color PEWTER;
        static Color VIRIDIAN;
        static Color GOLDENROD;
        static Color MAHOGANY;
        static Color VIOLET;
        static Color CINNABAR;

        mut_u8 r;
        mut_u8 g;
        mut_u8 b;
        mut_u8 opacity;

        static u8 BITS_PER_COLOR_COMPONENT = sizeof(r) * BITS_IN_BYTE;
        static u8 BITS_PER_PIXEL = BITS_PER_COLOR_COMPONENT * 4;

        mut_Color()
        {
            b = 0;
            g = 0;
            r = 0;
            opacity = 255;
        }
        mut_Color(u8 _r, u8 _g, u8 _b, u8 _a = 255)
        {
            b = _b;
            g = _g;
            r = _r;
            opacity = _a;
        }
        mut_Color(f32 _r, f32 _g, f32 _b, f32 _a)
        {
            b = (u8)(_b * 255.999f);
            g = (u8)(_g * 255.999f);
            r = (u8)(_r * 255.999f);
            opacity = (u8)(_a * 255.999f);
        }
        mut_Color(u32 color_code)
        {
            r = (u8)(color_code >> 24);
            g = (u8)((color_code & 0x00FF0000) >> 16);
            b = (u8)((color_code & 0x0000FF00) >> 8);
            opacity = (u8)(color_code & 0x000000FF);
        }
        mut_Color(i32 color_code)
        {
            r = (u8)(color_code >> 24);
            g = (u8)((color_code & 0x00FF0000) >> 16);
            b = (u8)((color_code & 0x0000FF00) >> 8);
            opacity = (u8)(color_code & 0x000000FF);
        }
        mut_Color(v3_ref v, u8 _a = 255)
        {
            v3 norm_v = (v.Norm() + v3::ONE) * 0.5f;
            r = (u8)(norm_v.x * 255.999f);
            g = (u8)(norm_v.y * 255.999f);
            b = (u8)(norm_v.z * 255.999f);
            opacity = _a;
        }

        MAY_INLINE static Color Lerp(Color from, Color to, f32 f)
        {
            f32 from_rf = from.r;
            f32 from_gf = from.b;
            f32 from_bf = from.b;
            f32 from_a = from.opacity;

            f32 to_rf = to.r;
            f32 to_gf = to.b;
            f32 to_bf = to.b;
            f32 to_a = to.opacity;

            f32 one_minus_a = 1.0f - f;
            u8 new_r = (u8)(from_rf * one_minus_a + to_rf * f);
            u8 new_g = (u8)(from_gf * one_minus_a + to_gf * f);
            u8 new_b = (u8)(from_bf * one_minus_a + to_bf * f);
            u8 new_a = (u8)(from_a * one_minus_a + to_a * f);
            return Color(new_r, new_g, new_b, new_a);
        }

        // Linearly interpolate from one color to another based on a
        MAY_INLINE static Color Mix(Color from, Color to, f32 f)
        {
            f32 from_rf = from.r;
            f32 from_gf = from.b;
            f32 from_bf = from.b;
            f32 from_a = from.opacity;

            f32 to_rf = to.r;
            f32 to_gf = to.b;
            f32 to_bf = to.b;
            f32 to_a = to.opacity;

            f32 one_minus_a = 1.0f - f;
            u8 new_r = (u8)(from_rf * one_minus_a + to_rf * f);
            u8 new_g = (u8)(from_gf * one_minus_a + to_gf * f);
            u8 new_b = (u8)(from_bf * one_minus_a + to_bf * f);
            u8 new_a = (u8)(from_a * one_minus_a + to_a * f);
            return Color(new_r, new_g, new_b, new_a);
        }

        INLINE Color Luminance() const noexcept
        {
            f32 rY = LUMA_REC709_R * LinearToGamma(r);
            f32 gY = LUMA_REC709_G * LinearToGamma(g);
            f32 bY = LUMA_REC709_B * LinearToGamma(b);
            u8 new_r = (u8)(rY * 255.999f);
            u8 new_g = (u8)(gY * 255.999f);
            u8 new_b = (u8)(bY * 255.999f);
            return Color(new_r, new_g, new_b, opacity);
        }

        INLINE u32 GetU32() const noexcept { return *(u32ptr(&r)); }
        INLINE operator u32() const noexcept { return GetU32(); }

        INLINE i32 GetI32() const noexcept { return *(i32ptr(&r)); }
        INLINE operator i32() const noexcept { return GetI32(); }

        INLINE Color_ref operator=(Color_ref rhs) noexcept
        {
            b = rhs.b;
            g = rhs.g;
            r = rhs.r;
            opacity = rhs.opacity;
            return *this;
        }
        INLINE Color_ref operator=(u32 color_code) noexcept
        {
            r = (u8)(color_code >> 24);
            g = (u8)((color_code & 0x00FF0000) >> 16);
            b = (u8)((color_code & 0x0000FF00) >> 8);
            opacity = (u8)(color_code & 0x000000FF);
            return *this;
        }
        INLINE Color_ref operator=(i32 color_code) noexcept
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

    class alignas(4) mut_Oklab
    {
    public:

        static Oklab BLACK;
        static Oklab LIGHT_GRAY;
        static Oklab GRAY;
        static Oklab DARK_GRAY;
        static Oklab WHITE;

        static Oklab RED;
        static Oklab GREEN;
        static Oklab BLUE;
        static Oklab CYAN;
        static Oklab MAGENTA;
        static Oklab YELLOW;

        static Oklab ORANGE;
        static Oklab PURPLE;
        static Oklab LAVENDER;
        static Oklab IVORY;
        static Oklab BURGUNDY;
        static Oklab SKY_BLUE;
        static Oklab OLIVE;
        static Oklab FOREST_GREEN;
        static Oklab OXBLOOD;
        static Oklab OXFORD_BLUE;
        static Oklab TURQUOISE;
        static Oklab CHARTREUSE;
        static Oklab SALMON;
        static Oklab BROWN;
        static Oklab RUST;
        static Oklab TEAL;
        static Oklab COBALT;
        static Oklab EGGPLANT;
        static Oklab PINK;
        static Oklab KEY_LIME;

        static Oklab LILAC;
        static Oklab MAROON;
        static Oklab BEIGE;
        static Oklab TAN;
        static Oklab PEACH;
        static Oklab LEMON;
        static Oklab LIME;
        static Oklab NAVY_BLUE;

        // https://colornames.org/color/80c0ff
        static Oklab MISALI;

        static Oklab GOLD;
        static Oklab SILVER;
        static Oklab RUBY;
        static Oklab SAPPHIRE;
        static Oklab EMERALD;
        static Oklab DIAMOND;
        static Oklab PEARL;
        static Oklab PLATINUM;
        static Oklab CELADON;
        static Oklab FUCHSIA;
        static Oklab SAFFRON;
        static Oklab CERULEAN;
        static Oklab INDIGO;
        static Oklab PEWTER;
        static Oklab VIRIDIAN;
        static Oklab GOLDENROD;
        static Oklab MAHOGANY;
        static Oklab VIOLET;
        static Oklab CINNABAR;

        mut_f32 L = 0.0f;
        mut_f32 a = 0.0f;
        mut_f32 b = 0.0f;
        mut_f32 opacity = 0.0f;

        mut_Oklab() {}
        mut_Oklab(f32 _l, f32 _a, f32 _b, f32 _opacity = 1.0f)
        {
            L = _l;
            a = _a;
            b = _b;
            opacity = _opacity;
        }
        mut_Oklab(Color_ref c)
        {
            mut_f32 rf = c.r * INV_U8_MAX;
            mut_f32 gf = c.g * INV_U8_MAX;
            mut_f32 bf = c.b * INV_U8_MAX;

            f32 l = 0.4122214708f * rf + 0.5363325363f * gf + 0.0514459929f * bf;
            f32 m = 0.2119034982f * rf + 0.6806995451f * gf + 0.1073969566f * bf;
            f32 s = 0.0883024619f * rf + 0.2817188376f * gf + 0.6299787005f * bf;

            f32 l_ = cbrtf(l);
            f32 m_ = cbrtf(m);
            f32 s_ = cbrtf(s);

            L = 0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_;
            a = 1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_;
            b = 0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_;
            opacity = c.opacity * INV_U8_MAX;
        }

        INLINE v3 ToRGB() const noexcept
        {
            f32 l_ = L + 0.3963377774f * a + 0.2158037573f * b;
            f32 m_ = L - 0.1055613458f * a - 0.0638541728f * b;
            f32 s_ = L - 0.0894841775f * a - 1.2914855480f * b;

            f32 l = l_ * l_ * l_;
            f32 m = m_ * m_ * m_;
            f32 s = s_ * s_ * s_;

            return {
                +4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
                -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
                -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
            };
        }
    };

    class alignas(4) mut_Colorf
    {
    public:

        mut_f32 r;
        mut_f32 g;
        mut_f32 b;
        mut_f32 opacity;

        static u8 BITS_PER_COLOR_COMPONENT = sizeof(r) * BITS_IN_BYTE;
        static u8 BITS_PER_PIXEL = BITS_PER_COLOR_COMPONENT * 4;

        mut_Colorf()
        {
            r = 0.0f;
            g = 0.0f;
            b = 0.0f;
            opacity = 1.0f;
        }
        mut_Colorf(u8 _r, u8 _g, u8 _b, u8 _a)
        {
            r = _r * INV_U8_MAX;
            g = _g * INV_U8_MAX;
            b = _b * INV_U8_MAX;
            opacity = _a * INV_U8_MAX;
        }
        mut_Colorf(f32 _r, f32 _g, f32 _b, f32 _a = 1.0f)
        {
            r = _r;
            g = _g;
            b = _b;
            opacity = _a;
        }
        mut_Colorf(Color_ref c)
        {
            r = c.r * INV_U8_MAX;
            g = c.g * INV_U8_MAX;
            b = c.b * INV_U8_MAX;
            opacity = c.opacity * INV_U8_MAX;
        }
        mut_Colorf(v3_ref v, f32 _a = 1.0f)
        {
            v3 norm_v = (v.Norm() + v3::ONE) * 0.5f;
            r = norm_v.x;
            g = norm_v.y;
            b = norm_v.z;
            opacity = _a;
        }
        mut_Colorf(Oklab_ref oklab)
        {
            f32 l_ = oklab.L + 0.3963377774f * oklab.a + 0.2158037573f * oklab.b;
            f32 m_ = oklab.L - 0.1055613458f * oklab.a - 0.0638541728f * oklab.b;
            f32 s_ = oklab.L - 0.0894841775f * oklab.a - 1.2914855480f * oklab.b;

            f32 l = l_ * l_ * l_;
            f32 m = m_ * m_ * m_;
            f32 s = s_ * s_ * s_;

            r = +4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s;
            g = -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s;
            b = -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s;
            opacity = oklab.opacity;
        }

        INLINE Oklab ToOklab() const noexcept
        {
            f32 l = 0.4122214708f * r + 0.5363325363f * g + 0.0514459929f * b;
            f32 m = 0.2119034982f * r + 0.6806995451f * g + 0.1073969566f * b;
            f32 s = 0.0883024619f * r + 0.2817188376f * g + 0.6299787005f * b;

            f32 l_ = cbrtf(l);
            f32 m_ = cbrtf(m);
            f32 s_ = cbrtf(s);

            return {
                0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_,
                1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_,
                0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_,
            };
        }

        INLINE Colorf ToRGB(Oklab_ref oklab)
        {
            f32 l_ = oklab.L + 0.3963377774f * oklab.a + 0.2158037573f * oklab.b;
            f32 m_ = oklab.L - 0.1055613458f * oklab.a - 0.0638541728f * oklab.b;
            f32 s_ = oklab.L - 0.0894841775f * oklab.a - 1.2914855480f * oklab.b;

            f32 l = l_ * l_ * l_;
            f32 m = m_ * m_ * m_;
            f32 s = s_ * s_ * s_;

            return {
                +4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
                -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
                -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
            };
        }

        MAY_INLINE static Colorf Lerp(Colorf from, Colorf to, f32 a)
        {
            f32 one_minus_a = 1.0f - a;
            f32 new_r = from.r * one_minus_a + to.r * a;
            f32 new_g = from.g * one_minus_a + to.g * a;
            f32 new_b = from.b * one_minus_a + to.b * a;
            f32 new_a = from.opacity * one_minus_a + to.opacity * a;
            return Colorf(new_r, new_g, new_b, new_a);
        }

        // Linearly interpolate from one color to another based on a
        MAY_INLINE static Colorf Mix(Oklab_ref from, Oklab_ref to, f32 a)
        {
            f32 one_minus_a = 1.0f - a;
            f32 new_L = from.L * one_minus_a + to.L * a;
            f32 new_A = from.a * one_minus_a + to.a * a;
            f32 new_B = from.b * one_minus_a + to.b * a;
            f32 new_a = from.opacity * one_minus_a + to.opacity * a;
            Oklab oklab = mut_Oklab(new_L, new_A, new_B, new_a);
            return Colorf(oklab.ToRGB(), oklab.opacity);
        }

        INLINE f32 LinearToGamma(f32 linear_color_component) const noexcept
        {
            return powf(linear_color_component, INV_GAMMA);
        }
        INLINE f32 GammaToLinear(f32 gamma_color_component) const noexcept
        {
            return powf(gamma_color_component, GAMMA);
        }
        INLINE Colorf ToLinear() const noexcept
        {
            return Colorf(LinearToGamma(r), LinearToGamma(g), LinearToGamma(b), opacity);
        }
        INLINE Colorf ToGamma() const noexcept
        {
            return Colorf(GammaToLinear(r), GammaToLinear(g), GammaToLinear(b), opacity);
        }

        INLINE Colorf Luminance() const noexcept
        {
            f32 rY = LUMA_REC709_R * LinearToGamma(r);
            f32 gY = LUMA_REC709_G * LinearToGamma(g);
            f32 bY = LUMA_REC709_B * LinearToGamma(b);
            return Colorf(rY, gY, bY, opacity);
        }

        INLINE Color ToColor() const noexcept { return Color(r, g, b, opacity); }
        INLINE operator Color() const noexcept { return ToColor(); }

        INLINE Colorf_ref operator=(Colorf_ref rhs) noexcept
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
    Color Color::BLACK = Color(0x000000ff);
    Color Color::WHITE = Color(0xffffffff);
    Color Color::RED =   Color(0xff0000ff);
    Color Color::GREEN = Color(0x00ff00ff);
    Color Color::BLUE =  Color(0x0000ffff);
    Color Color::CYAN =  Color(0x00ffffff);
    Color Color::MAGENTA =Color(0xff00ffff);
    Color Color::YELLOW = Color(0xffff00ff);

    // very common colors according to:
    //      https://www.color-hex.com/color-names.html ,
    //      https://simple.wikipedia.org/wiki/Colour ,
    //      and random colors I liked
    Color Color::DARK_GRAY = Color(0x262626ff);
    Color Color::GRAY = Color(0x7f7f7fff);
    Color Color::LIGHT_GRAY = Color(0xd9d9d9ff);
    Color Color::ORANGE = Color(0xffa500ff);
    Color Color::PURPLE = Color(0xa020f0ff);
    Color Color::LAVENDER = Color(0xb57edcff);
    Color Color::IVORY = Color(0xfffff0ff);
    Color Color::BURGUNDY = Color(0x800020ff);
    Color Color::SKY_BLUE = Color(0x00ccffff);
    Color Color::OLIVE = Color(0x808000ff);
    Color Color::FOREST_GREEN = Color(0x228b22ff);
    Color Color::OXBLOOD = Color(0x4a0000ff);
    Color Color::OXFORD_BLUE = Color(0x002147ff);
    Color Color::TURQUOISE = Color(0x40e0d0ff);
    Color Color::CHARTREUSE = Color(0x76ee00ff);
    Color Color::SALMON = Color(0xfa8072ff);
    Color Color::BROWN = Color(0x654321ff);
    Color Color::RUST = Color(0xb7410eff);
    Color Color::TEAL = Color(0x008080ff);
    Color Color::COBALT = Color(0x0047abff);
    Color Color::EGGPLANT = Color(0x614051ff);
    Color Color::PINK = Color(0xfc8eacff);
    Color Color::KEY_LIME = Color(0xe8f48cff);
    Color Color::LILAC = Color(0xc8a2c8ff);
    Color Color::MAROON = Color(0xb03060ff);
    Color Color::BEIGE = Color(0xf5f5dcff);
    Color Color::TAN = Color(0xd2b48cff);
    Color Color::PEACH = Color(0xffe5b4ff);
    Color Color::LEMON = Color(0xfff700ff);
    Color Color::LIME = Color(0x32cd32ff);
    Color Color::NAVY_BLUE = Color(0x1974d2ff);
    Color Color::MISALI = Color(0x80c0ffff);

    // Pokemon Colors
    Color Color::GOLD = Color(0xffd700ff);
    Color Color::SILVER = Color(0xc0c0c0ff);
    Color Color::RUBY = Color(0xe0115fff);
    Color Color::SAPPHIRE = Color(0x0f52baff);
    Color Color::EMERALD = Color(0x50c878ff);
    Color Color::DIAMOND = Color(0xb9f2ffff);
    Color Color::PEARL = Color(0xff5733ff);
    Color Color::PLATINUM = Color(0xe5e4e2ff);
    Color Color::CELADON = Color(0xace1afff);
    Color Color::FUCHSIA = Color(0xfe4164ff);
    Color Color::SAFFRON = Color(0xf4c430ff);
    Color Color::CERULEAN = Color(0x007ba7ff);
    Color Color::INDIGO = Color(0x4b0082ff);
    Color Color::PEWTER = Color(0x8ba8b7ff);
    Color Color::VIRIDIAN = Color(0x40826dff);
    Color Color::GOLDENROD = Color(0xdaa520ff);
    Color Color::MAHOGANY = Color(0xc04000ff);
    Color Color::VIOLET = Color(0xee82eeff);
    Color Color::CINNABAR = Color(0xe34234ff);

    // OKLAB COLORS ===================================================

    Oklab Oklab::BLACK = Oklab(Color::BLACK);
    Oklab Oklab::WHITE = Oklab(Color::WHITE);
    Oklab Oklab::RED = Oklab(Color::RED);
    Oklab Oklab::GREEN = Oklab(Color::GREEN);
    Oklab Oklab::BLUE = Oklab(Color::BLUE);
    Oklab Oklab::CYAN = Oklab(Color::CYAN);
    Oklab Oklab::MAGENTA = Oklab(Color::MAGENTA);
    Oklab Oklab::YELLOW = Oklab(Color::YELLOW);
    Oklab Oklab::DARK_GRAY = Oklab(Color::DARK_GRAY);
    Oklab Oklab::GRAY = Oklab(Color::GRAY);
    Oklab Oklab::LIGHT_GRAY = Oklab(Color::LIGHT_GRAY);
    Oklab Oklab::ORANGE = Oklab(Color::ORANGE);
    Oklab Oklab::PURPLE = Oklab(Color::PURPLE);
    Oklab Oklab::LAVENDER = Oklab(Color::LAVENDER);
    Oklab Oklab::IVORY = Oklab(Color::IVORY);
    Oklab Oklab::BURGUNDY = Oklab(Color::BURGUNDY);
    Oklab Oklab::SKY_BLUE = Oklab(Color::SKY_BLUE);
    Oklab Oklab::OLIVE = Oklab(Color::OLIVE);
    Oklab Oklab::FOREST_GREEN = Oklab(Color::FOREST_GREEN);
    Oklab Oklab::OXBLOOD = Oklab(Color::OXBLOOD);
    Oklab Oklab::OXFORD_BLUE = Oklab(Color::OXFORD_BLUE);
    Oklab Oklab::TURQUOISE = Oklab(Color::TURQUOISE);
    Oklab Oklab::CHARTREUSE = Oklab(Color::CHARTREUSE);
    Oklab Oklab::SALMON = Oklab(Color::SALMON);
    Oklab Oklab::BROWN = Oklab(Color::BROWN);
    Oklab Oklab::RUST = Oklab(Color::RUST);
    Oklab Oklab::TEAL = Oklab(Color::TEAL);
    Oklab Oklab::COBALT = Oklab(Color::COBALT);
    Oklab Oklab::EGGPLANT = Oklab(Color::EGGPLANT);
    Oklab Oklab::PINK = Oklab(Color::PINK);
    Oklab Oklab::KEY_LIME = Oklab(Color::KEY_LIME);
    Oklab Oklab::LILAC = Oklab(Color::LILAC);
    Oklab Oklab::MAROON = Oklab(Color::MAROON);
    Oklab Oklab::BEIGE = Oklab(Color::BEIGE);
    Oklab Oklab::TAN = Oklab(Color::TAN);
    Oklab Oklab::PEACH = Oklab(Color::PEACH);
    Oklab Oklab::LEMON = Oklab(Color::LEMON);
    Oklab Oklab::LIME = Oklab(Color::LIME);
    Oklab Oklab::NAVY_BLUE = Oklab(Color::NAVY_BLUE);
    Oklab Oklab::MISALI = Oklab(Color::MISALI);
    Oklab Oklab::GOLD = Oklab(Color::GOLD);
    Oklab Oklab::SILVER = Oklab(Color::SILVER);
    Oklab Oklab::RUBY = Oklab(Color::RUBY);
    Oklab Oklab::SAPPHIRE = Oklab(Color::SAPPHIRE);
    Oklab Oklab::EMERALD = Oklab(Color::EMERALD);
    Oklab Oklab::DIAMOND = Oklab(Color::DIAMOND);
    Oklab Oklab::PEARL = Oklab(Color::PEARL);
    Oklab Oklab::PLATINUM = Oklab(Color::PLATINUM);
    Oklab Oklab::CELADON = Oklab(Color::CELADON);
    Oklab Oklab::FUCHSIA = Oklab(Color::FUCHSIA);
    Oklab Oklab::SAFFRON = Oklab(Color::SAFFRON);
    Oklab Oklab::CERULEAN = Oklab(Color::CERULEAN);
    Oklab Oklab::INDIGO = Oklab(Color::INDIGO);
    Oklab Oklab::PEWTER = Oklab(Color::PEWTER);
    Oklab Oklab::VIRIDIAN = Oklab(Color::VIRIDIAN);
    Oklab Oklab::GOLDENROD = Oklab(Color::GOLDENROD);
    Oklab Oklab::MAHOGANY = Oklab(Color::MAHOGANY);
    Oklab Oklab::VIOLET = Oklab(Color::VIOLET);
    Oklab Oklab::CINNABAR = Oklab(Color::CINNABAR);

    // OKLAB COLORS ===================================================
}