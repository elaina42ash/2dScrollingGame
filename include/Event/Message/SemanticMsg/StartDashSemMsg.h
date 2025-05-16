#pragma once
#include "Event/Message/IEventMessage.h"

class StartDashSemMsg:public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
