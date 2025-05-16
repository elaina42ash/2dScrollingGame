#pragma once
#include "Event/Listener/IMessageListener.h"
#include "Fwk/Collision/CollisionShape.h"

class ICollisionComponent : virtual public IComponent, public IMessageListener
{
public:
	virtual ~ICollisionComponent() override = default;

	virtual Fwk::Collision::ShapeType GetShapeType() const = 0;

	virtual Fwk::Collision::Circle GetShapeCircle() const = 0;

	virtual Fwk::Collision::Rect GetShapeRect() const = 0;
};
