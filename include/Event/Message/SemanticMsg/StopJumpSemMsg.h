#pragma once
#include "Event/Message/IEventMessage.h"

class StopJumpSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
