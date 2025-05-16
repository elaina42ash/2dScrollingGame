#pragma once
#include "Component/Common/IComponent.h"

class ITileMapSensorComponent : virtual public IComponent
{
public:
	virtual ~ITileMapSensorComponent() override = default;

	virtual  bool IsInsideWall(Lib::Math::Vector2f _position) const = 0;
};
