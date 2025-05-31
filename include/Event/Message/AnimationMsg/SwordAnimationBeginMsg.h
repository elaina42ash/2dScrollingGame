#pragma once
#include "Event/Message/IEventMessage.h"

class SwordAnimationBeginMsg :public  IEventMessage
{
private:
	int animationID_;

public:
	explicit SwordAnimationBeginMsg(int _animationId);

	TypeidSystem::TypeID GetTypeID() const override;

	int GetAnimationID() const;
};
