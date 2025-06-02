#pragma once
#include "Event/Message/IEventMessage.h"

class StartInteractSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
