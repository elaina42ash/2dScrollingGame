#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"

SwordAnimationBeginMsg::SwordAnimationBeginMsg(int _animationId): animationID_(_animationId)
{
}

TypeidSystem::TypeID SwordAnimationBeginMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<SwordAnimationBeginMsg>();
}

int SwordAnimationBeginMsg::GetAnimationID() const
{
	return animationID_;
}
