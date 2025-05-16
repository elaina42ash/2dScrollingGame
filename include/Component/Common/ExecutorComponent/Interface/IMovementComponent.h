#pragma once
#include "Event/Listener/IMessageListener.h"

class IMovementComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual  ~IMovementComponent() override = default;

};
