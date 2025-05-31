#include "Event/Message/AnimationMsg\KatanaAnimationKeyframeMsg.h"
KatanaAnimationKeyframeMsg::KatanaAnimationKeyframeMsg(int _animationId, int _keyFrameIndex): animationID_(_animationId),
	keyFrameIndex_(_keyFrameIndex)
{
}

TypeidSystem::TypeID KatanaAnimationKeyframeMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<KatanaAnimationKeyframeMsg>();
}

int KatanaAnimationKeyframeMsg::GetAnimationID() const
{
	return animationID_;
}

int KatanaAnimationKeyframeMsg::GetKeyFrameIndex() const
{
	return keyFrameIndex_;
}
