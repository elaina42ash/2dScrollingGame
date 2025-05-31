#pragma once
#include "Component/Common/IComponent.h"
#include "Lib/Math/TVector2.h"

class ITileMapSensorComponent : virtual public IComponent
{
public:
	virtual ~ITileMapSensorComponent() override = default;

	virtual bool IsInsideWall(const Lib::Math::Vector2f& _position) const = 0;
};
