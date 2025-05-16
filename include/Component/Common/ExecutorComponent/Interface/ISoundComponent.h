#pragma once
#include "Component/Common/IComponent.h"
#include "Event/Listener/IMessageListener.h"

class ISoundComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual  ~ISoundComponent() override = default;
};
