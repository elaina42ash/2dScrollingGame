#pragma once
#include "Message.h"
#include "command/ICommand.h"


class InputMessage : public Message
{
private:
	ICommand* cmd_;

public:
	InputMessage( ICommand* _cmd);

	const ICommand* GetCommand() const;

	typeid_system::TypeID GetTypeID() const override;
};
