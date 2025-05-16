#pragma once
#include "Event/Message/IEventMessage.h"

class SetIsDeadConditionMsg : public IEventMessage
{
private:
	bool value_ = false;

public:
	explicit SetIsDeadConditionMsg(bool _value);

	bool GetValue() const;

	TypeidSystem::TypeID GetTypeID() const override;
};
