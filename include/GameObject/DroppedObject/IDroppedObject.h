#pragma once
#include "GameObject/IGameObject.h"

class IDroppedObject : virtual public IGameObject
{
public:
	virtual  ~IDroppedObject() = default;
};
