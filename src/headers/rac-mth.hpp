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
}
