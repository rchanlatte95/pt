#pragma once
#include "rac-v2.hpp"

namespace rac::mth
{
    class alignas(8) mut_v2i;
    typedef mut_v2i* mut_v2i_ptr;
    typedef mut_v2i& mut_v2i_ref;
    typedef const mut_v2i v2i;
    typedef const mut_v2i* v2i_ptr;
    typedef const mut_v2i& v2i_ref;

    class alignas(8) mut_v2i
    {
    public:
        static u64 COMPONENT_CT = 2;
        static u64 MAX_STR_LEN = COMPONENT_CT * (F32_STR_CHAR_CT + COMMA_SPACE_LEN);

        static v2i ZERO;

        static v2i ONE;
        static v2i SIGN_ONE;

        static v2i RIGHT;
        static v2i UP;
        static v2i LEFT;
        static v2i DOWN;

        mut_i32 x;
        mut_i32 y;

        mut_v2i();
        mut_v2i(i32 v);
        mut_v2i(i32 x_, i32 y_);
        mut_v2i(f32 x_, f32 y_);

        INLINE v2i operator-() const noexcept;
        INLINE i32 operator[](i32 i) const noexcept;
        INLINE mut_i32ref operator[](i32 i);

        INLINE v2i_ref operator+=(v2i v) noexcept;
        INLINE v2i_ref operator-=(v2i v) noexcept;
        INLINE v2i_ref operator*=(i32 v) noexcept;
        INLINE v2i_ref operator/=(i32 v) noexcept;

        INLINE f32 SqrMag() const noexcept;
        INLINE f32 InvSqrMag() const noexcept;
        INLINE f32 Mag() const noexcept;
        INLINE f32 InvMag() const noexcept;
        INLINE v2 Norm() const noexcept;
    };

    INLINE v2i operator*(v2i_ref u, f32 v);
    INLINE v2i operator/(v2i_ref u, f32 v);
    INLINE v2i operator*(v2i_ref u, i32 v);
    INLINE v2i operator/(v2i_ref u, i32 v);

    INLINE v2i operator+(v2i_ref u, v2i_ref v);
    INLINE v2i operator-(v2i_ref u, v2i_ref v);
    INLINE v2i operator*(v2i_ref u, v2i_ref v);
    INLINE v2i operator/(v2i_ref u, v2i_ref v);

    INLINE i32 Dot(v2i_ref u, v2i_ref v) noexcept;
    MAY_INLINE v2i Min(const std::vector<v2i_ref>& nums);
    MAY_INLINE v2i Max(const std::vector<v2i_ref>& nums);
    MAY_INLINE void MapTo01(std::vector<v2i_ref>& vec2remap);
}