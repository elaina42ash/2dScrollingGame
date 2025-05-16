#pragma once
#include "Event/Message/IEventMessage.h"

class AttackInputMsg : public IEventMessage
{
public:
	AttackInputMsg() = default;

	TypeidSystem::TypeID GetTypeID() const override;
};
