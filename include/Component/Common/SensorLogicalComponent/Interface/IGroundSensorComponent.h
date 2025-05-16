#pragma once
class IGroundSensorComponent : virtual public IComponent
{
public:
	virtual  ~IGroundSensorComponent() override = default;
	virtual bool Detected() = 0;
};
