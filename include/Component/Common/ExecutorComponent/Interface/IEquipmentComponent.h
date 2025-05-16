#pragma once
#include "Event/Listener/IMessageListener.h"

class IEquipmentComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual  ~IEquipmentComponent() override = default;
	virtual bool IsAttacking() = 0;
};
