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

        INLINE mut_v3_ref operator=(v3_ref v_ref) noexcept
        {
            x = v_ref.x;
            y = v_ref.y;
            z = v_ref.z;
            return *this;
        }

        INLINE mut_v3_ref operator+=(v3_ref v) noexcept
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        INLINE mut_v3_ref operator-=(v3_ref v) noexcept
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        INLINE mut_v3_ref operator*=(f32 v) noexcept
        {
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }
        INLINE mut_v3_ref operator/=(f32 v) noexcept
        {
            return *this *= 1.0f / v;
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
            f32 invMag = this->InvMag();
            return v3(x * invMag, y * invMag, z * invMag);
        }

        INLINE pf128 Pack128() const noexcept
        {
            return pf128(x, y, z, 0.0f);
        }

        INLINE static_strings::mut_cachestr ToStr(u32 decimal_places = 4) const noexcept
        {
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            static_strings::mut_cachestr res;
            bool use_exp = Between(x, MAX_F32_FOR_FULL_REP) ||
                            Between(y, MAX_F32_FOR_FULL_REP) ||
                            Between(z, MAX_F32_FOR_FULL_REP);

            switch (decimal_places)
            {
            case 0:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.0e, %.0e, %.0e)" : "(%.0f, %.0f, %.0f)", x, y, z);
                break;
            case 1:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.1e, %.1e, %.1e)" : "(%.1f, %.1f, %.1f)", x, y, z);
                break;
            case 2:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.2e, %.2e, %.2e)" : "(%.2f, %.2f, %.2f)", x, y, z);
                break;
            case 3:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.3e, %.3e, %.3e)" : "(%.3f, %.3f, %.3f)", x, y, z);
                break;
            default:
                snprintf(res.ToCharPtr(), MAX, use_exp ? "(%.4e, %.4e, %.4e)" : "(%.4f, %.4f, %.4f)", x, y, z);
                break;
            }
            res.Resize();
            return res;
        }
    };

    INLINE v3 operator*(v3_ref u, f32 v) { return v3(u.x * v, u.y * v, u.z * v); }
    INLINE v3 operator/(v3_ref u, f32 v) { return u * (1.0f / v); }
    INLINE v3 operator*(v3_ref u, i32 v) { return v3(u.x * (f32)v, u.y * (f32)v, u.z * (f32)v); }
    INLINE v3 operator/(v3_ref u, i32 v) { return u * (f32)(1.0f / (f32)v); }

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

    v3 v3::ZERO = v3(0.0f);

    v3 v3::ONE = v3(1.0f);
    v3 v3::SIGN_ONE = -ONE;

    v3 v3::RIGHT =      v3(1.0f, 0.0f, 0.0f);
    v3 v3::UP =         v3(0.0f, 1.0f, 0.0f);
    v3 v3::FORWARD =    v3(0.0f, 0.0f, 1.0f);
    v3 v3::LEFT = -RIGHT;
    v3 v3::DOWN = -UP;
    v3 v3::BACKWARD = -FORWARD;
}