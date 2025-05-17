#pragma once
#include "Lib/Math/TVector2.h"

class IEnvironmentQuery
{
public:
	virtual  ~IEnvironmentQuery() = default;

	virtual bool IsInsideWallCircle(const Lib::Math::Vector2f& _position, float _radius) const = 0;

	virtual bool IsInsideWallRect(const Lib::Math::Vector2f& _position, float _width, float _height) const = 0;

	virtual Lib::Math::Vector2f GetMapSize()const = 0;

	virtual float GetTileSize() const = 0;
};
