#pragma once
class IInputComponent : virtual public IComponent
{
public:
	virtual ~IInputComponent() override = default;
};
