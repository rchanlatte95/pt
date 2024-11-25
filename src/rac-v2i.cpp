#include "headers/rac-v2i.hpp"

namespace rac::mth
{
    v2i v2i::ZERO = v2i(0);
    v2i v2i::ONE = v2i(1);
    v2i v2i::SIGN_ONE = -ONE;

    v2i v2i::RIGHT = v2i(1, 0);
    v2i v2i::UP = v2i(0, 1);
    v2i v2i::LEFT = -RIGHT;
    v2i v2i::DOWN = -UP;

    mut_v2i::mut_v2i()
    {
        x = 0;
        y = 0;
    }
    mut_v2i::mut_v2i(i32 v)
    {
        x = v;
        y = v;
    }
    mut_v2i::mut_v2i(i32 x_, i32 y_)
    {
        x = x_;
        y = y_;
    }
    mut_v2i::mut_v2i(f32 x_, f32 y_)
    {
        x = (i32)x_;
        y = (i32)y_;
    }

    INLINE v2i mut_v2i::operator-() const noexcept
    {
        return mut_v2i(-x, -y);
    }
    INLINE i32 mut_v2i::operator[](i32 i) const noexcept
    {
        return *(&x + i);
    }
    INLINE mut_i32ref mut_v2i::operator[](i32 i)
    {
        return *(&x + i);
    }

    INLINE v2i_ref mut_v2i::operator+=(v2i v) noexcept
    {
        x += v.x;
        y += v.y;
    }
    INLINE v2i_ref mut_v2i::operator-=(v2i v) noexcept
    {
        x -= v.x;
        y -= v.y;
    }
    INLINE v2i_ref mut_v2i::operator*=(i32 v) noexcept
    {
        x *= v;
        y *= v;
    }
    INLINE v2i_ref mut_v2i::operator/=(i32 v) noexcept
    {
        x /= v;
        y /= v;
    }

    INLINE f32 mut_v2i::SqrMag() const noexcept
    {
        return (f32)(x * x + y * y);
    }
    INLINE f32 mut_v2i::InvSqrMag() const noexcept
    {
        return 1.0f / (f32)(x * x + y * y);
    }
    INLINE f32 mut_v2i::Mag() const noexcept
    {
        return sqrtf(this->SqrMag());
    }
    INLINE f32 mut_v2i::InvMag() const noexcept
    {
        return 1.0f / sqrtf(this->SqrMag());
    }
    INLINE v2 mut_v2i::Norm() const noexcept
    {
        f32 invMag = this->InvMag();
        return mut_v2(x * invMag, y * invMag);
    }

    INLINE v2i operator*(v2i_ref u, f32 v)
    {
        return v2i(u.x * v, u.y * v);
    }
    INLINE v2i operator/(v2i_ref u, f32 v)
    {
        return u * (1.0f / v);
    }
    INLINE v2i operator*(v2i_ref u, i32 v)
    {
        return v2i(u.x * v, u.y * v);
    }
    INLINE v2i operator/(v2i_ref u, i32 v)
    {
        return u * (1.0f / v);
    }

    INLINE v2i operator+(v2i_ref u, v2i_ref v)
    {
        return v2i(u.x + v.x, u.y + v.y);
    }
    INLINE v2i operator-(v2i_ref u, v2i_ref v)
    {
        return v2i(u.x - v.x, u.y - v.y);
    }
    INLINE v2i operator*(v2i_ref u, v2i_ref v)
    {
        return v2i(u.x * v.x, u.y * v.y);
    }
    INLINE v2i operator/(v2i_ref u, v2i_ref v)
    {
        return v2i(u.x / v.x, u.y / v.y);
    }

    INLINE i32 Dot(v2i_ref u, v2i_ref v) noexcept
    {
        return u.x * v.x + u.y * v.y;
    }

    MAY_INLINE v2i Min(const std::vector<mut_v2i>& nums)
    {
        i64 len = nums.size();
        if (len < 1)
        {
            return v2i::ZERO;
        }

        switch (len)
        {
        case 0: return v2i::ZERO;
        case 1: return nums[0];
        case 2:
            return v2i(nums[0].x < nums[1].x ? nums[0].x : nums[1].x,
                nums[0].y < nums[1].y ? nums[0].y : nums[1].y);

        default:
            mut_v2i min = nums[0];
            for (mut_i64 i = 1; i < len; ++i)
            {
                if (nums[i].x < min.x)
                {
                    min.x = nums[i].x;
                }
                if (nums[i].y < min.y)
                {
                    min.y = nums[i].y;
                }
            }
            return min;
        }
    }
    MAY_INLINE v2i Max(const std::vector<mut_v2i>& nums)
    {
        i64 len = nums.size();
        if (len < 1)
        {
            return v2i::ZERO;
        }

        switch (len)
        {
        case 0: return v2i::ZERO;
        case 1: return nums[0];
        case 2:
            return v2i(nums[0].x > nums[1].x ? nums[0].x : nums[1].x,
                nums[0].y > nums[1].y ? nums[0].y : nums[1].y);

        default:
            mut_v2i max = nums[0];
            for (mut_i64 i = 1; i < len; ++i)
            {
                if (nums[i].x > max.x)
                {
                    max.x = nums[i].x;
                }
                if (nums[i].y > max.y)
                {
                    max.y = nums[i].y;
                }
            }
            return max;
        }
    }
}