#pragma once
#include "Lib/Math/TVector2.h"

class ISceneContext
{
public:
	virtual ~ISceneContext() = default;

	virtual float GetTileSize() = 0;

	virtual bool IsInsideWallRect(Lib::Math::Vector2f _position, float _width, float _height) const = 0;

	virtual bool IsInsideWallCircle(Lib::Math::Vector2f _position, float _radius) const = 0;
};
