#pragma once
#include "Event/Message/IEventMessage.h"

class StartKnockBackSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
