#pragma once
#include "IGameObject.h"

class IStaticObject : virtual public IGameObject
{
public:
	virtual  ~IStaticObject() = default;
};
