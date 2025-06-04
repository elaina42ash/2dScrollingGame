#pragma once
#include "Event/Message/IEventMessage.h"

class StartGameVectorySemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
