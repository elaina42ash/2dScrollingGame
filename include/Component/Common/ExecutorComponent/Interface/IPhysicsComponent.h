#pragma once
#include "Lib/Math/TVector2.h"
#include "Event/Listener/IMessageListener.h"

class IPhysicsComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual ~IPhysicsComponent() override = default;

	virtual Lib::Math::Vector2f GetVelocity() const = 0;

	virtual void ClearVerticalVelocity() = 0;
};
