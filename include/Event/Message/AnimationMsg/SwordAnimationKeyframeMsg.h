#pragma once
#include "Event/Message/IEventMessage.h"

class SwordAnimationKeyframeMsg : public IEventMessage
{
private:
	int animationID_;
	int keyFrameIndex_;

public:
	SwordAnimationKeyframeMsg(int _animationId, int _keyFrameIndex);

public:
	TypeidSystem::TypeID GetTypeID() const override;

	int GetAnimationID () const;

	int GetKeyFrameIndex() const;
};
