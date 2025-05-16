#include "command/Command.h"

Command::Command(CommandType _type): command_(_type)
{
}

const ICommand::CommandType& Command::GetCmdType()
{
	return command_;
}
