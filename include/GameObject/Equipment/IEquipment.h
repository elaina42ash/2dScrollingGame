#pragma once
#include "EquipmentDef.h"
#include "GameObject/IGameObject.h"

class IEquipment :public virtual IGameObject
{
public:
	virtual  ~IEquipment() = default;

	virtual EquipmentStatus GetEquipmentStatus() = 0;

	virtual EquipmentType GetEquipmentType() const = 0;

};
