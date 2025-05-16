#pragma once
#include <type_traits>

#include "Lib/Math/TVector2.h"

namespace GameMath
{
	bool FloatIsZero(float _value, float _epsilon = 1e-6f);

	float Dot(const Lib::Math::Vector2f& _a, const Lib::Math::Vector2f& _b);

	float LengthSquared(const Lib::Math::Vector2f& v);

	template<typename T>
	T Clamp(const T& _value,const T& _min,const T& _max)
	{
		static_assert(std::is_arithmetic<T>::value, "Clamp only supports arithmetic types.");

		if (_value < _min)
			return _min;
		else if (_value > _max)
			return _max;
		return _value;
	}
}
