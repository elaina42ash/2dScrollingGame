#include "Event/Message/ChangeStateMessage.h"

ChangeStateMessage::ChangeStateMessage(const ChangeStateMessageParams& _params):Message(MessageType::CHANGE_STATE),params_(_params)
{
}

const ChangeStateMessage::ChangeStateMessageParams& ChangeStateMessage::GetChangeStateParams() const
{
	return params_;
}

typeid_system::TypeID ChangeStateMessage::GetTypeID() const
{
	return typeid_system::GetTypeID<ChangeStateMessage>();
}
