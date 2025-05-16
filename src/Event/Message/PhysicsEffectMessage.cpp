#include "Event/Message/PhysicsEffectMessage.h"
PhysicsEffectMessage::PhysicsEffectMessage( const PhysicsEffectMessageParams& _params):Message(MessageType::EFFECT),  params_(_params)
{
}

const PhysicsEffectMessage::PhysicsEffectMessageParams& PhysicsEffectMessage::GetParams() const
{
	return params_;
}

typeid_system::TypeID PhysicsEffectMessage::GetTypeID() const
{
	return typeid_system::GetTypeID<PhysicsEffectMessage>();
}
