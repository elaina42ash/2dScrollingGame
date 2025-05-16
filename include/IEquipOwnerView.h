#pragma once
#include "GameDef.h"
#include "Lib/Math/TVector2.h"

class IEquipOwnerView 
{
public:
	virtual ~IEquipOwnerView() = default;

	virtual Direction GetDirection() const = 0;
	virtual Lib::Math::Vector2f GetPosition() const = 0;
	virtual float GetPositionX() const = 0;
	virtual float GetPositionY() const = 0;
};
