#pragma once
#include "Component/Common/IComponent.h"
#include "Event/Listener/IMessageListener.h"

class IAnimationComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual ~IAnimationComponent() override = default;

};
