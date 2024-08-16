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

        INLINE const mut_v3 operator-() const noexcept
        {
            return mut_v3(-x, -y, -z);
        }
        INLINE f32 operator[](i32 i) const noexcept { return *(&x + i); }
        INLINE mut_f32ref operator[](i32 i) { return *(&x + i); }

        INLINE const mut_v3& operator+=(const mut_v3 v) noexcept
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }
        INLINE const mut_v3& operator-=(const mut_v3 v) noexcept
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }
        INLINE const mut_v3& operator*=(f32 v) noexcept
        {
            x *= v;
            y *= v;
            z *= v;
        }
        INLINE const mut_v3& operator/=(f32 v) noexcept
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
        INLINE const mut_v3 Norm() const noexcept
        {
            f32 invMag = this->InvMag();
            return mut_v3(x * invMag, y * invMag, z * invMag);
        }

        INLINE static_strings::mut_cachestr ToStr(u32 decimal_places = 4) const noexcept
        {
            u64 MAX = static_strings::MAX_CACHESTR_LEN;
            static_strings::mut_cachestr res;
            bool use_exp = (x >= MAX_F32_FOR_FULL_REP || x <= MIN_F32_FOR_FULL_REP) ||
                        (y >= MAX_F32_FOR_FULL_REP || y <= MIN_F32_FOR_FULL_REP) ||
                        (z >= MAX_F32_FOR_FULL_REP || z <= MIN_F32_FOR_FULL_REP);

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