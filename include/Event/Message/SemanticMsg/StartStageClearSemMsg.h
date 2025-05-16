#pragma once
#include "Event/Message/IEventMessage.h"

class StartStageClearSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
