#pragma once
#include "Lib/Math/TVector2.h"

class IDroppedObjectView
{
public:
	virtual  ~IDroppedObjectView() = default;

	virtual Lib::Math::Vector2f GetVelocity() const = 0;

	virtual float GetVelocityX() const = 0;

	virtual float GetVelocityY() const = 0;

	virtual Lib::Math::Vector2f GetPosition() const = 0;

	virtual  float GetPositionX() const = 0;

	virtual float GetPositionY() const = 0;

	virtual float GetTileSize() const = 0;

	virtual bool IsInsideWallRect(Lib::Math::Vector2f _position, float _width, float _height) const = 0;

	virtual bool IsInsideWallCircle(Lib::Math::Vector2f _position, float _radius) const = 0;
};
