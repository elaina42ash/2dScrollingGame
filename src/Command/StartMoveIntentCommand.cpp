#include "command/StartMoveIntentCommand.h"

StartMoveIntentCommand::StartMoveIntentCommand(const Lib::Math::Vector2f& _moveInput): Command(CommandType::START_MOVE),moveInput_(_moveInput)
{
}

const Lib::Math::Vector2f& StartMoveIntentCommand::GetMoveInput() const
{
	return moveInput_;
}

TypeidSystem::TypeID StartMoveIntentCommand::GetTypeID() const
{
	return TypeidSystem::GetTypeID<StartMoveIntentCommand>();
}
