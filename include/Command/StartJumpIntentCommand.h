#pragma once
#pragma once
#include "Command.h"

class StartJumpIntentCommand : public Command
{
public:
	explicit StartJumpIntentCommand();

	TypeidSystem::TypeID GetTypeID() const override;
};
