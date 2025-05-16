#include "Event/Message/AnimationMessage.h"

AnimationMessage::AnimationMessage( const AnimationMessageParams& _params) :Message(MessageType::ANIMATION),  params_(_params)
{
}


const AnimationMessage::AnimationMessageParams& AnimationMessage::GetParams() const
{
	return params_;
}

typeid_system::TypeID AnimationMessage::GetTypeID() const
{
	return typeid_system::GetTypeID<AnimationMessage>();
}
