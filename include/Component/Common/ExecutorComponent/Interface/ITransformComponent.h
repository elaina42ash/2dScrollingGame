#pragma once
#include "Lib/Math/TVector2.h"
#include "GameDef.h"
#include "Event/Listener/IMessageListener.h"

class ITransformComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual  ~ITransformComponent() override = default;

	virtual const Lib::Math::Vector2f& GetPosition() const = 0;

	virtual void Translate(const Lib::Math::Vector2f& _offset) = 0;

	virtual void ChangeDirection(const Direction& _new) = 0;

	virtual Direction GetDirection() const = 0;

	virtual void MoveTo(const Lib::Math::Vector2f& _target) = 0;

	virtual float GetPositionY() const = 0;

	virtual float GetPositionX() const = 0;

	virtual  void ReverseDirection() = 0;
};
