#pragma once
#include "GameDef.h"

#include "Lib/Math/TVector2.h"

class IWeaponView
{
public:
	virtual ~IWeaponView() = default;
	virtual  Lib::Math::Vector2f GetPosition() const = 0;
	virtual float GetPositionX() const = 0;
	virtual float GetPositionY() const = 0;
	virtual bool IsAttacking() const = 0;
	virtual Direction GetDirection() const = 0;
};
