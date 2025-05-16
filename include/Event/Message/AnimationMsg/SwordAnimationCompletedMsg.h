#pragma once
#include "Event/Message/IEventMessage.h"

class SwordAnimationCompletedMsg : public IEventMessage
{
private:
	int animationID_;

public:
	explicit SwordAnimationCompletedMsg(int _animationId);

	TypeidSystem::TypeID GetTypeID() const override;

	int GetAnimationID() const;
};
