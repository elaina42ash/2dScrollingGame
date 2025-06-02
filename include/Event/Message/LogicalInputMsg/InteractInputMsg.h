#pragma once
#include "Event/Message/IEventMessage.h"

class InteractInputMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
