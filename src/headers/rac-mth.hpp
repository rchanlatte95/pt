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
	f32 DEG2RAD = PI / 180.0f; // π / 180
	f32 RAD2DEG = 180.0f / PI; // 180 / π

	f32 LN_2PI = 1.83787706641f; // ln(2π)
	f32 LN_10 = 2.30258509299f; // ln(10)
	f32 HALF_LN_2PI = LN_2PI * 0.5f; // ln(2π) / 2
	f32 INV_LN_2PI = 1.0f / LN_2PI; // 1 / ln(2π)
}
