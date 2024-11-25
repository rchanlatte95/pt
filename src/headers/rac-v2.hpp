#pragma once
#include "rac.hpp"

namespace rac::mth
{
    class alignas(8) mut_v2;
    typedef mut_v2* mut_v2_ptr;
    typedef mut_v2& mut_v2_ref;
    typedef const mut_v2 v2;
    typedef const mut_v2* v2_ptr;
    typedef const mut_v2& v2_ref;

    class alignas(8) mut_v2
    {
    public:
        static u64 COMPONENT_CT = 2;
        static u64 MAX_STR_LEN = COMPONENT_CT * (F32_STR_CHAR_CT + COMMA_SPACE_LEN);

        static v2 ZERO;

        static v2 ONE;
        static v2 SIGN_ONE;

        static v2 RIGHT;
        static v2 UP;
        static v2 LEFT;
        static v2 DOWN;

        mut_f32 x;
        mut_f32 y;

        mut_v2();
        mut_v2(f32 v);
        mut_v2(f32 x_, f32 y_);

        INLINE const mut_v2 operator-() const noexcept;
        INLINE f32 operator[](i32 i) const noexcept;
        INLINE mut_f32ref operator[](i32 i);

        INLINE const mut_v2& operator+=(const mut_v2 v) noexcept;
        INLINE const mut_v2& operator-=(const mut_v2 v) noexcept;
        INLINE const mut_v2& operator*=(f32 v) noexcept;
        INLINE const mut_v2& operator/=(f32 v) noexcept;

        INLINE f32 SqrMag() const noexcept;
        INLINE f32 InvSqrMag() const noexcept;
        INLINE f32 Mag() const noexcept;
        INLINE f32 InvMag() const noexcept;
        INLINE const mut_v2 Norm() const noexcept;
    };

    INLINE v2 operator*(v2_ref u, f32 v);
    INLINE v2 operator/(v2_ref u, f32 v);
    INLINE v2 operator*(v2_ref u, i32 v);
    INLINE v2 operator/(v2_ref u, i32 v);

    INLINE v2 operator+(v2_ref u, v2_ref v);
    INLINE v2 operator-(v2_ref u, v2_ref v);
    INLINE v2 operator*(v2_ref u, v2_ref v);
    INLINE v2 operator/(v2_ref u, v2_ref v);

    INLINE v2 Norm(v2_ref v) noexcept;
    INLINE f32 Dot(v2_ref u, v2_ref v) noexcept;
    MAY_INLINE v2 Min(const std::vector<mut_v2>& nums);
    MAY_INLINE v2 Max(const std::vector<mut_v2>& nums);
    MAY_INLINE void MapTo01(std::vector<mut_v2>& vec2remap);
}