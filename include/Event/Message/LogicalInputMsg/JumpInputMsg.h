#pragma once
#include "Event/Message/IEventMessage.h"

class JumpInputMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};

