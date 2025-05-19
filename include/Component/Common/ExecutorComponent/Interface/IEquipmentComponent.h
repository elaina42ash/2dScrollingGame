#pragma once
#include "Event/Listener/IMessageListener.h"

class IEquipmentComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual  ~IEquipmentComponent() override = default;
	virtual bool IsAttacking() = 0;
	virtual bool GetActiveWeaponID_() const = 0;
};
