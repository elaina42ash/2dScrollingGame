#pragma once
#include "Event/Message/IEventMessage.h"

class StartIdleSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
