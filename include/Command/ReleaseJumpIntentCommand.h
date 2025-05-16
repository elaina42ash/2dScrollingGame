#pragma once
#include "Command.h"

class ReleaseJumpIntentCommand:public Command
{
public:
	explicit ReleaseJumpIntentCommand();

	TypeidSystem::TypeID GetTypeID() const override;
};