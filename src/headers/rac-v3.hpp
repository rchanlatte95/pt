#pragma once
#include "rac-mth.hpp"
#include "rac-v2.hpp"
#include "rac-staticstr.hpp"
#include "rac-cachestr.hpp"
#include "rac-packedtypes.hpp"

namespace rac::mth
{
    class mut_v3;
    typedef mut_v3* mut_v3_ptr;
    typedef mut_v3& mut_v3_ref;
    typedef const mut_v3 v3;
    typedef const mut_v3* v3_ptr;
    typedef const mut_v3& v3_ref;
    class mut_v3
    {
    public:
        static u64 COMPONENT_CT = 3;
        static u64 MAX_STR_LEN = COMPONENT_CT * (F32_STR_CHAR_CT + COMMA_SPACE_LEN) + NULL_TERMINATOR_LEN;

        static v3 ZERO;

        static v3 ONE;
        static v3 SIGN_ONE;

        static v3 RIGHT;
        static v3 UP;
        static v3 FORWARD;
        static v3 LEFT;
        static v3 DOWN;
        static v3 BACKWARD;

        mut_f32 x;
        mut_f32 y;
        mut_f32 z;

        mut_v3();
        mut_v3(f32 v);
        mut_v3(f32 x_, f32 y_);
        mut_v3(f32 x_, f32 y_, f32 z_);
        mut_v3(v2 v, f32 z_ = 0.0f);

        INLINE v3 operator-() const noexcept;
        INLINE f32 operator[](i32 i) const noexcept;
        INLINE mut_f32ref operator[](i32 i);

        INLINE mut_v3_ref operator=(v3_ref v_ref) noexcept;
        INLINE mut_v3_ref operator+=(v3_ref v) noexcept;
        INLINE mut_v3_ref operator-=(v3_ref v) noexcept;
        INLINE mut_v3_ref operator*=(f32 v) noexcept;
        INLINE mut_v3_ref operator/=(f32 v) noexcept;

        INLINE f32 SqrMag() const noexcept;
        INLINE f32 InvSqrMag() const noexcept;
        INLINE f32 Mag() const noexcept;
        INLINE f32 InvMag() const noexcept;
        INLINE v3 Norm() const noexcept;
        INLINE pf128 Pack128() const noexcept;
        INLINE static_strings::mut_cachestr ToStr(u32 decimal_places = 4) const noexcept;
    };

    INLINE v3 operator*(v3_ref u, f32 v);
    INLINE v3 operator/(v3_ref u, f32 v);
    INLINE v3 operator*(v3_ref u, i32 v);
    INLINE v3 operator/(v3_ref u, i32 v);

    INLINE v3 operator+(v3_ref u, v3_ref v);
    INLINE v3 operator-(v3_ref u, v3_ref v);
    INLINE v3 operator*(v3_ref u, v3_ref v);
    INLINE v3 operator/(v3_ref u, v3_ref v);

    INLINE v3 Norm(v3_ref v) noexcept;
    INLINE f32 Dot(v3_ref u, v3_ref v) noexcept;
    INLINE v3 Cross(v3_ref u, v3_ref v) noexcept;
}