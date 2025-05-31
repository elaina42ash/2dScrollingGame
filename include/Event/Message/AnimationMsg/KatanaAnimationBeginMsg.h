#pragma once
#include "TypeID.h"
#include "Event/Message/IEventMessage.h"

class KatanaAnimationBeginMsg :public  IEventMessage
{
private:
	int animationID_;

public:
	explicit KatanaAnimationBeginMsg(int _animationId);

	TypeidSystem::TypeID GetTypeID() const override;

	int GetAnimationID() const;
};
