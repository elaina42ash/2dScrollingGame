#pragma once
#include "Event/Message/IEventMessage.h"

class StartAttackSemMsg : public IEventMessage
{
public:
	StartAttackSemMsg() = default;

	TypeidSystem::TypeID GetTypeID() const override;
};
