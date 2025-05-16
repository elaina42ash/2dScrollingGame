#pragma once
#include "StateMachine/State/Player/PlayerState.h"

class EndDashSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
