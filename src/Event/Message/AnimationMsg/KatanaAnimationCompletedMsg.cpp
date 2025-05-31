#include "Event/Message/AnimationMsg/KatanaAnimationCompletedMsg.h"

KatanaAnimationCompletedMsg::KatanaAnimationCompletedMsg(int _animationId): animationID_(_animationId)
{
}

TypeidSystem::TypeID KatanaAnimationCompletedMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<KatanaAnimationCompletedMsg>();
}

int KatanaAnimationCompletedMsg::GetAnimationID() const
{
	return animationID_;
}
