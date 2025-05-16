#pragma once
#include "Event/Message/IEventMessage.h"

class StartJumpSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
