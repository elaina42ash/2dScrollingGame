#pragma once
#include "Event/Message/IEventMessage.h"

class SwordAnimationBeginMsg :public  IEventMessage
{
private:
	int animationID_;

public:
	explicit SwordAnimationBeginMsg(int _animationId)
		: animationID_(_animationId)
	{
	}

	TypeidSystem::TypeID GetTypeID() const override
	{
		return TypeidSystem::GetTypeID<SwordAnimationBeginMsg>();
	}

	int GetAnimationID() const
	{
		return animationID_;
	}
};
