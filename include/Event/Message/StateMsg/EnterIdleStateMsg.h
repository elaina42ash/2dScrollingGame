#pragma once
#include "Event/Message/IEventMessage.h"

class EnterIdleStateMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
