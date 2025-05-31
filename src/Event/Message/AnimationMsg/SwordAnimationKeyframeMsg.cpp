#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"

SwordAnimationKeyframeMsg::SwordAnimationKeyframeMsg(int _animationId, int _keyFrameIndex): animationID_(_animationId),
	keyFrameIndex_(_keyFrameIndex)
{
}

TypeidSystem::TypeID SwordAnimationKeyframeMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<SwordAnimationKeyframeMsg>();
}

int SwordAnimationKeyframeMsg::GetAnimationID() const
{
	return animationID_;
}

int SwordAnimationKeyframeMsg::GetKeyFrameIndex() const
{
	return keyFrameIndex_;
}
