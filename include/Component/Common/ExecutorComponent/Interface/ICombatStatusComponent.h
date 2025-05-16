#pragma once
#include "Event/Listener/IMessageListener.h"

class ICombatStatusComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual  ~ICombatStatusComponent() override = default;

	virtual int GetRemainingInvincibilityFrames() const = 0;

	virtual bool IsInvincible() const = 0;
};
