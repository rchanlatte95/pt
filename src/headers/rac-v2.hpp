#pragma once

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

        mut_v2()
        {
            x = 0.0f;
            y = 0.0f;
        }
        mut_v2(f32 v)
        {
            x = v;
            y = v;
        }
        mut_v2(f32 x_, f32 y_)
        {
            x = x_;
            y = y_;
        }

        INLINE const mut_v2 operator-() const noexcept { return mut_v2(-x, -y); }
        INLINE f32 operator[](i32 i) const noexcept { return *(&x + i); }
        INLINE mut_f32ref operator[](i32 i) { return *(&x + i); }

        INLINE const mut_v2& operator+=(const mut_v2 v) noexcept
        {
            x += v.x;
            y += v.y;
        }
        INLINE const mut_v2& operator-=(const mut_v2 v) noexcept
        {
            x -= v.x;
            y -= v.y;
        }
        INLINE const mut_v2& operator*=(f32 v) noexcept
        {
            x *= v;
            y *= v;
        }
        INLINE const mut_v2& operator/=(f32 v) noexcept
        {
            *this *= 1.0f / v;
        }

        INLINE f32 SqrMag() const noexcept { return x * x + y * y; }
        INLINE f32 InvSqrMag() const noexcept
        {
            return 1.0f / (x * x + y * y);
        }
        INLINE f32 Mag() const noexcept
        {
            return sqrtf(this->SqrMag());
        }
        INLINE f32 InvMag() const noexcept
        {
            return 1.0f / sqrtf(this->SqrMag());
        }
        INLINE const mut_v2 Norm() const noexcept
        {
            f32 invMag = this->InvMag();
            return mut_v2(x * invMag, y * invMag);
        }
    };

    INLINE v2 operator*(v2_ref u, f32 v) { return u * v; }
    INLINE v2 operator/(v2_ref u, f32 v) { return u * (1.0f / v); }

    INLINE v2 operator+(v2_ref u, v2_ref v)
    {
        return v2(u.x + v.x, u.y + v.y);
    }
    INLINE v2 operator-(v2_ref u, v2_ref v)
    {
        return v2(u.x - v.x, u.y - v.y);
    }
    INLINE v2 operator*(v2_ref u, v2_ref v)
    {
        return v2(u.x * v.x, u.y * v.y);
    }
    INLINE v2 operator/(v2_ref u, v2_ref v)
    {
        return v2(u.x / v.x, u.y / v.y);
    }

    INLINE v2 Norm(v2_ref v) noexcept { return v * v.InvMag(); }
    INLINE f32 Dot(v2_ref u, v2_ref v) noexcept
    {
        return u.x * v.x + u.y * v.y;
    }

    v2 v2::ZERO = v2(0.0f);

    v2 v2::ONE = v2(1.0f);
    v2 v2::SIGN_ONE = -ONE;

    v2 v2::RIGHT = v2(1.0f, 0.0f);
    v2 v2::UP = v2(0.0f, 1.0f);
    v2 v2::LEFT = -RIGHT;
    v2 v2::DOWN = -UP;
}