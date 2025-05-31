#include "Event/Message/AnimationMsg/KatanaAnimationBeginMsg.h"

KatanaAnimationBeginMsg::KatanaAnimationBeginMsg(int _animationId): animationID_(_animationId)
{
}

TypeidSystem::TypeID KatanaAnimationBeginMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<KatanaAnimationBeginMsg>();
}

int KatanaAnimationBeginMsg::GetAnimationID() const
{
	return animationID_;
}
