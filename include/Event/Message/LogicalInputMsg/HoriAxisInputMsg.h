#pragma once
#include "Event/Message/IEventMessage.h"

class HoriAxisInputMsg : public IEventMessage
{
private:
	float value_ = 0.0f;

public:
	explicit HoriAxisInputMsg(float _value);

	TypeidSystem::TypeID GetTypeID() const override;

	float GetValue() const;
};

