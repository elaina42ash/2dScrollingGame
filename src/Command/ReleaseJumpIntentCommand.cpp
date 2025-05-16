#include "Command/ReleaseJumpIntentCommand.h"

ReleaseJumpIntentCommand::ReleaseJumpIntentCommand():Command(CommandType::RELEASE_JUMP)
{
}

TypeidSystem::TypeID ReleaseJumpIntentCommand::GetTypeID() const
{
	return TypeidSystem::GetTypeID<ReleaseJumpIntentCommand>();
}

