#include "command/StartJumpIntentCommand.h"

StartJumpIntentCommand::StartJumpIntentCommand(): Command(CommandType::START_JUMP)
{
}

TypeidSystem::TypeID StartJumpIntentCommand::GetTypeID() const
{
	return TypeidSystem::GetTypeID<StartJumpIntentCommand>();
}
