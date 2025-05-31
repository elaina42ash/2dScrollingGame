#pragma once
#include "Event/Message/IEventMessage.h"

class KatanaAnimationKeyframeMsg : public IEventMessage
{
private:
	int animationID_;
	int keyFrameIndex_;
public:
	KatanaAnimationKeyframeMsg(int _animationId, int _keyFrameIndex);

	TypeidSystem::TypeID GetTypeID() const override;

	int GetAnimationID() const;

	int GetKeyFrameIndex() const;
};
