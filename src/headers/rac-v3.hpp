#pragma once
#include <cstdio>

#include "rac.hpp"
#include "rac-v2.hpp"
#include "rac-staticstr.hpp"
#include "rac-cachestr.hpp"

namespace rac::mth
{
    class mut_v3
    {
    public:
        static u64 COMPONENT_CT = 3;
        static u64 MAX_STR_LEN = COMPONENT_CT * (F32_STR_CHAR_CT + COMMA_SPACE_LEN) + NULL_TERMINATOR_LEN;

        mut_f32 x;
        mut_f32 y;
        mut_f32 z;

        mut_v3()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
        mut_v3(f32 v)
        {
            x = v;
            y = v;
            z = v;
        }
        mut_v3(f32 x_, f32 y_)
        {
            x = x_;
            y = y_;
            z = 0.0f;
        }
        mut_v3(f32 x_, f32 y_, f32 z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }
        mut_v3(v2 v, f32 z_ = 0.0f)
        {
            x = v.x;
            y = v.y;
            z = z_;
        }

        INLINE v3 operator-() const noexcept { return v3(-x, -y, -z); }
        INLINE f32 operator[](i32 i) const noexcept { return *(&x + i); }
        INLINE mut_f32ref operator[](i32 i) { return *(&x + i); }

        INLINE mut_v3_ref operator+=(v3 v) noexcept
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }
        INLINE mut_v3_ref operator-=(v3 v) noexcept
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }
        INLINE mut_v3_ref operator*=(f32 v) noexcept
        {
            x *= v;
            y *= v;
            z *= v;
        }
        INLINE mut_v3_ref operator/=(f32 v) noexcept
        {
            *this *= 1.0f / v;
        }

        INLINE f32 SqrMag() const noexcept
        {
            return x * x + y * y + z * z;
        }
        INLINE f32 InvSqrMag() const noexcept
        {
            return 1.0f / (x * x + y * y + z * z);
        }
        INLINE f32 Mag() const noexcept
        {
            return sqrtf(this->SqrMag());
        }
        INLINE f32 InvMag() const noexcept
        {
            return 1.0f / sqrtf(this->SqrMag());
        }
        INLINE v3 Norm() const noexcept
        {
            return *this * this->InvMag();
        }

        INLINE static_strings::cachestr ToStr(u32 decimal_places = 4) const noexcept
        {
            static_strings::cachestr res;
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            bool need_sci_notation = (x >= MAX_F32_FOR_FULL_REP || x <= MIN_F32_FOR_FULL_REP) ||
                                    (y >= MAX_F32_FOR_FULL_REP || y <= MIN_F32_FOR_FULL_REP) ||
                                    (z >= MAX_F32_FOR_FULL_REP || z <= MIN_F32_FOR_FULL_REP);

            switch (decimal_places)
            {
            case 0:
                cstr fmt0 = need_sci_notation ? "(%.0f, %.0f, %.0f)" : "(%.0e, %.0e, %.0e)";
                snprintf(res.ToCharPtr(), MAX, fmt0, x, y, z);
                break;
            case 1:
                cstr fmt1 = need_sci_notation ? "(%.1f, %.1f, %.1f)" : "(%.1e, %.1e, %.1e)";
                snprintf(res.ToCharPtr(), MAX, fmt1, x, y, z);
                break;
            case 2:
                cstr fmt2 = need_sci_notation ? "(%.2f, %.2f, %.2f)" : "(%.2e, %.2e, %.2e)";
                snprintf(res.ToCharPtr(), MAX, fmt2, x, y, z);
                break;
            case 3:
                cstr fmt3 = need_sci_notation ? "(%.3f, %.3f, %.3f)" : "(%.3e, %.3e, %.3e)";
                snprintf(res.ToCharPtr(), MAX, fmt3, x, y, z);
                break;
            default:
                cstr fmt_ = need_sci_notation ? "(%.4f, %.4f, %.4f)" : "(%e, %e, %e)";
                snprintf(res.ToCharPtr(), MAX, fmt_, x, y, z);
                break;
            }
            return res;
        }
    };

    typedef mut_v3* mut_v3_ptr;
    typedef mut_v3& mut_v3_ref;
    typedef const mut_v3 v3;
    typedef const mut_v3* v3_ptr;
    typedef const mut_v3& v3_ref;

    INLINE v3 operator*(v3_ref u, f32 v) { return u * v; }
    INLINE v3 operator/(v3_ref u, f32 v) { return u * (1.0f / v); }

    INLINE v3 operator+(v3_ref u, v3_ref v)
    {
        return v3(u.x + v.x, u.y + v.y, u.z + v.z);
    }
    INLINE v3 operator-(v3_ref u, v3_ref v)
    {
        return v3(u.x - v.x, u.y - v.y, u.z - v.z);
    }
    INLINE v3 operator*(v3_ref u, v3_ref v)
    {
        return v3(u.x * v.x, u.y * v.y, u.z * v.z);
    }
    INLINE v3 operator/(v3_ref u, v3_ref v)
    {
        return v3(u.x / v.x, u.y / v.y, u.z / v.z);
    }

    INLINE v3 Norm(v3_ref v) noexcept { return v * v.InvMag(); }
    INLINE f32 Dot(v3_ref u, v3_ref v) noexcept
    {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }
    INLINE v3 Cross(v3_ref u, v3_ref v) noexcept
    {
        return v3(u.y * v.z - u.z * v.y,
                    u.z * v.x - u.x * v.z,
                    u.x * v.y - u.y * v.x);
    }
}