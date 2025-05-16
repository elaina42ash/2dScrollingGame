#pragma once
#include "Event/Message/IEventMessage.h"

class ReleaseJumpInputMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
