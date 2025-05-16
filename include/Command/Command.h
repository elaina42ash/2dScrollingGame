#pragma once
#include "ICommand.h"

class Command : public ICommand
{
private:
	CommandType command_;

public:
	explicit Command(CommandType _type);

	const CommandType& GetCmdType() override final;
};
