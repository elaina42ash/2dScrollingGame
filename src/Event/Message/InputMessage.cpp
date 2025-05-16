#include "Event/Message/InputMessage.h"

InputMessage::InputMessage(ICommand* _cmd) : Message(MessageType::INPUT),
cmd_(_cmd)
{
}

const ICommand* InputMessage::GetCommand() const
{
	return cmd_;
}

typeid_system::TypeID InputMessage::GetTypeID() const
{
	return typeid_system::GetTypeID<InputMessage>();
}
