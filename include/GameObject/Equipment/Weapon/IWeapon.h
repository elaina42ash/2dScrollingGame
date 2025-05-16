#pragma once
#include "WeaponDef.h"

class IWeapon
{
public:
	virtual ~IWeapon() = default;

	virtual void Attack() = 0;
	virtual void EndAttack() = 0;
	virtual bool CanAttack() const = 0;
	virtual bool IsAttacking() const = 0;
	virtual void Equip() = 0;
	virtual WeaponMode GetMode() const = 0;
};
