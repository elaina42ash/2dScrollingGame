#include "GameMath.h"

#include <cmath>

bool GameMath::FloatIsZero(const float _value, const float _epsilon)
{
	return fabs(_value) < _epsilon;
}

float GameMath::Dot(const Lib::Math::Vector2f& _a, const Lib::Math::Vector2f& _b)
{
	return _a.x * _b.x + _a.y * _b.y;
}

float GameMath::LengthSquared(const Lib::Math::Vector2f& v)
{
	return v.x * v.x + v.y * v.y;
}
