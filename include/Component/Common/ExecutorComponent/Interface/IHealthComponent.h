#pragma once
#include "Event/Listener/IMessageListener.h"

class IHealthComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual ~IHealthComponent() override = default;

	virtual int GetHp() const = 0;

	virtual int GetMaxHp() const = 0;

	virtual float GetNormalizedHp() const = 0;

	virtual void AddHp(int _value) = 0;

	virtual  bool IsDead() const = 0;
};
