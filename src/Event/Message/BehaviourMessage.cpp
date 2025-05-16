#include "Event/Message/BehaviourMessage.h"

BehaviourMessage::BehaviourMessage(const BehaviourMessageParams& _params): Message(MessageType::BEHAVIOUR),
	params_(_params)
{
}

const BehaviourMessage::BehaviourMessageParams& BehaviourMessage::GetMoveParams() const
{
	return params_;
}

typeid_system::TypeID BehaviourMessage::GetTypeID() const
{
	return typeid_system::GetTypeID<BehaviourMessage>();
}
