#pragma once
#include "Event/Message/IEventMessage.h"

class DashInputMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
