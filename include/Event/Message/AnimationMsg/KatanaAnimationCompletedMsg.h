#pragma once
#include "Event/Message/IEventMessage.h"

class KatanaAnimationCompletedMsg : public IEventMessage
{
private:
	int animationID_;

public:
	explicit KatanaAnimationCompletedMsg(int _animationId);

	TypeidSystem::TypeID GetTypeID() const override;

	int GetAnimationID() const;
};
