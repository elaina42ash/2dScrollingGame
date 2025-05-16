#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"

SwordAnimationCompletedMsg::SwordAnimationCompletedMsg(int _animationId): animationID_(_animationId)
{
}

TypeidSystem::TypeID SwordAnimationCompletedMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<SwordAnimationCompletedMsg>();
}

int SwordAnimationCompletedMsg::GetAnimationID() const
{
	return animationID_;
}
