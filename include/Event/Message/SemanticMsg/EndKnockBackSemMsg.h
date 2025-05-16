#pragma once
#include "Event/Message/IEventMessage.h"

class EndKnockBackSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
