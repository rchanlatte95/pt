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

    class mut_Colorf;
    typedef mut_Colorf* mut_Colorf_ptr;
    typedef mut_Colorf& mut_Colorf_ref;
    typedef const mut_Colorf Colorf;
    typedef const mut_Colorf* Colorf_ptr;
    typedef const mut_Colorf& Colorf_ref;

    // these factors are grabbed from: https://en.wikipedia.org/wiki/Luma_(video)
    // under the section: Rec. 601 luma versus Rec. 709 luma coefficients
    // I am assuming most monitors in circulation are digital HD monitors.
    f32 LUMA_REC709_R = 0.2126f;
    f32 LUMA_REC709_G = 0.7152f;
    f32 LUMA_REC709_B = 0.0722f;
    f32 GAMMA = 2.2222222f;
    f32 INV_GAMMA = 1.0f / GAMMA;

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

        mut_Color();
        mut_Color(u8 _r, u8 _g, u8 _b, u8 _a = 255);
        mut_Color(f32 _r, f32 _g, f32 _b, f32 _a);
        mut_Color(u32 color_code);
        mut_Color(i32 color_code);
        mut_Color(v3_ref v, u8 _a = 255);

        // Linearly interpolate from one color to another based on a
        MAY_INLINE static Color Mix(Color from, Color to, f32 f);
        INLINE f32 LinearToGamma(f32 linear_color_component) const noexcept;
        INLINE f32 GammaToLinear(f32 gamma_color_component) const noexcept;
        INLINE Color Luminance() const noexcept;

        INLINE u32 GetU32() const noexcept;
        INLINE operator u32() const noexcept;
        INLINE i32 GetI32() const noexcept;
        INLINE operator i32() const noexcept;

        INLINE Color_ref operator=(Color_ref rhs) noexcept;
        INLINE Color_ref operator=(u32 color_code) noexcept;
        INLINE Color_ref operator=(i32 color_code) noexcept;

        INLINE static_strings::mut_cachestr ToStr() const noexcept;
        INLINE static_strings::mut_cachestr ToPpmStr() const noexcept;
    };

    class mut_Colorf
    {
    public:

        mut_f32 r;
        mut_f32 g;
        mut_f32 b;
        mut_f32 opacity;

        static u8 BITS_PER_COLOR_COMPONENT = sizeof(r) * BITS_IN_BYTE;
        static u8 BITS_PER_PIXEL = BITS_PER_COLOR_COMPONENT * 4;

        mut_Colorf();
        mut_Colorf(u8 _r, u8 _g, u8 _b, u8 _a);
        mut_Colorf(f32 _r, f32 _g, f32 _b, f32 _a = 1.0f);
        mut_Colorf(Color_ref c);
        mut_Colorf(v3_ref v, f32 _a = 1.0f);

        // Linearly interpolate from one color to another based on a
        MAY_INLINE static Colorf Mix(Colorf from, Colorf to, f32 a);
        INLINE f32 LinearToGamma(f32 linear_color_component) const noexcept;
        INLINE f32 GammaToLinear(f32 gamma_color_component) const noexcept;
        INLINE Colorf ToLinear() const noexcept;
        INLINE Colorf ToGamma() const noexcept;

        INLINE Colorf Luminance() const noexcept;

        INLINE Color ToColor() const noexcept;
        INLINE operator Color() const noexcept;

        INLINE Colorf_ref operator=(Colorf_ref rhs) noexcept;

        mut_f32 operator [] (i32 i) const;
        mut_f32ref operator [] (i32 i);

        INLINE static_strings::mut_cachestr ToStr(u32 decimal_places = 4) const noexcept;
    };
}