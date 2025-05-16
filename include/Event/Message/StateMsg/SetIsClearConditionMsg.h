#pragma once
#include "Event/Message/IEventMessage.h"

class SetIsClearConditionMsg : public IEventMessage
{
private:
	bool value_ = false;

public:
	explicit SetIsClearConditionMsg(bool _value);

	bool GetValue() const;

public:
	TypeidSystem::TypeID GetTypeID() const override;
};
