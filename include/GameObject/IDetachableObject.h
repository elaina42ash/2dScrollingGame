#pragma once
#include "GameObjectDef.h"
#include "IGameObject.h"

class IDetachableObject : virtual public IGameObject
{
public:
	virtual ~IDetachableObject() = default;

	virtual  DetachableObjectState GetState() const = 0;

};
