#pragma once
#include "rac.hpp"

namespace rac::mth
{
	constexpr bool Between(f32 x, f32 max_sgnmax)
	{
		return x > -max_sgnmax && x < max_sgnmax;
	}
	constexpr bool BetweenInclusive(f32 x, f32 max_sgnmax)
	{
		return x >= -max_sgnmax && x <= max_sgnmax;
	}
	constexpr bool Between(f32 x, f32 min, f32 max)
	{
		return x > min && x < max;
	}
	constexpr bool BetweenInclusive(f32 x, f32 min, f32 max)
	{
		return x >= min && x <= max;
	}

	constexpr f32 Min(const std::vector<mut_f32>& nums)
	{
		const i64 len = nums.size();
		if (len < 1)
		{
			return 0.0f;
		}

		switch (len)
		{
		case 0: return 0.0f;
		case 1: return nums[0];
		case 2: return nums[0] < nums[1] ? nums[0] : nums[1];
		case 3:
			if (nums[0] < nums[1])
			{
				return nums[0] < nums[2] ? nums[0] : nums[2];
			}
			else
			{
				return nums[1] < nums[2] ? nums[1] : nums[2];
			}
		default:
			mut_f32 min = nums[0];
			for (mut_i64 i = 1; i < len; ++i)
			{
				if (nums[i] < min)
				{
					min = nums[i];
				}
			}
			return min;
		}
	}
	constexpr f32 Max(const std::vector<mut_f32>& nums)
	{
		const i64 len = nums.size();
		if (len < 1)
		{
			return 0.0f;
		}

		switch (len)
		{
		case 0: return 0.0f;
		case 1: return nums[0];
		case 2: return nums[0] > nums[1] ? nums[0] : nums[1];
		case 3:
			if (nums[0] > nums[1])
			{
				return nums[0] > nums[2] ? nums[0] : nums[2];
			}
			else
			{
				return nums[1] > nums[2] ? nums[1] : nums[2];
			}
		default:
			mut_f32 max = nums[0];
			for (mut_i64 i = 1; i < len; ++i)
			{
				if (nums[i] > max)
				{
					max = nums[i];
				}
			}
			return max;
		}
	}
	MAY_INLINE void MapTo01(std::vector<mut_f32>& vec2remap)
	{
		f32 MIN = Min(vec2remap);
		f32 MAX = Max(vec2remap);
		f32 DELTA = 1.0f / (MAX - MIN);
		for (int i = 0; i < vec2remap.size(); ++i)
		{
			vec2remap[i] = (vec2remap[i] - MIN) * DELTA;
		}
	}

	f32 PI = 3.14159265f; // π
	f32 INV_PI = 1.0f / PI; // 1.0f / π
	f32 SIXTH_PI = PI / 6.0f;
	f32 FOURTH_PI = PI / 4.0f;
	f32 THIRD_PI = PI / 3.0f;
	f32 HALF_PI = PI / 2.0f;
	f32 TAU = 2.0f * PI; // 2π

	f32 ROOT_2 = 1.41421356f; // √2
	f32 ROOT_3 = 1.73205080f; // √3
	f32 ROOT_5 = 2.23606797f; // √5
	f32 ROOT_6 = 2.44948974f; // √6
	f32 ROOT_7 = 2.64575131f; // √7
	f32 ROOT_10 = 3.16227761f; // √10
	f32 ROOT_11 = 3.31662479f; // √11
	f32 ROOT_12 = 3.46410161f; // √12

	f32 HALF_ROOT_2 = ROOT_2 / 2.0f;
	f32 HALF_ROOT_3 = ROOT_3 / 2.0f;
	f32 HALF_ROOT_5 = ROOT_5 / 2.0f;
	f32 HALF_ROOT_6 = ROOT_6 / 2.0f;
	f32 HALF_ROOT_7 = ROOT_7 / 2.0f;
	f32 HALF_ROOT_10 = ROOT_10 / 2.0f;
	f32 HALF_ROOT_11 = ROOT_11 / 2.0f;
	f32 HALF_ROOT_12 = ROOT_12 / 2.0f;

	f32 INV_180 = 1.0f / 180.0f;
	f32 DEGREE_TO_RADIAN = PI / 180.0f; // π / 180
	f32 RADIAN_TO_DEGREE = 180.0f / PI; // 180 / π

	f32 LN_2PI = 1.83787706641f; // ln(2π)
	f32 LN_10 = 2.30258509299f; // ln(10)
	f32 HALF_LN_2PI = LN_2PI * 0.5f; // ln(2π) / 2
	f32 INV_LN_2PI = 1.0f / LN_2PI; // 1 / ln(2π)
}
