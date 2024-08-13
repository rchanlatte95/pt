#pragma once
#include "rac.hpp"

namespace rac::mth
{
    class alignas(8) mut_v2
    {
    public:

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

        INLINE v2 operator-() const noexcept { return v2(-x, -y); }
        INLINE f32 operator[](i32 i) const noexcept { return *(&x + i); }
        INLINE mut_f32ref operator[](i32 i) { return *(&x + i); }

        INLINE mut_v2_ref operator+=(v2 v) noexcept
        {
            x += v.x;
            y += v.y;
        }
        INLINE mut_v2_ref operator-=(v2 v) noexcept
        {
            x -= v.x;
            y -= v.y;
        }
        INLINE mut_v2_ref operator*=(f32 v) noexcept
        {
            x *= v;
            y *= v;
        }
        INLINE mut_v2_ref operator/=(f32 v) noexcept { *this *= 1.0f / v; }

        INLINE f32 SqrMag() const noexcept { return x * x + y * y; }
        INLINE f32 InvSqrMag() const noexcept { return 1.0f / (x * x + y * y); }
        INLINE f32 Mag() const noexcept { return sqrtf(this->SqrMag()); }
        INLINE f32 InvMag() const noexcept { return 1.0f / sqrtf(this->SqrMag()); }
        INLINE v2 Norm() const noexcept { return *this * this->InvMag(); }
    };

    typedef mut_v2* mut_v2_ptr;
    typedef mut_v2& mut_v2_ref;
    typedef const mut_v2 v2;
    typedef const mut_v2* v2_ptr;
    typedef const mut_v2& v2_ref;

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
}