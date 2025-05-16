#pragma once
#include "Event/Message/IEventMessage.h"

class SetIsDamagedConditionMsg : public IEventMessage
{
private:
	bool value_ = false;

public:
	explicit SetIsDamagedConditionMsg(bool _value);

	bool GetValue() const;

	TypeidSystem::TypeID GetTypeID() const override;
};
