#pragma once
#include "Component/Common/IComponent.h"

class ICeilingSensorComponent : virtual public IComponent
{
public:
	virtual  ~ICeilingSensorComponent() override = default;
	virtual bool Detected() = 0;
};
