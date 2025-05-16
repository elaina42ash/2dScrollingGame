#pragma once
#include "Event/Message/IEventMessage.h"

class StartHurtSemMsg : public IEventMessage
{
private:
	int incomingDamage = 0;
public:
	explicit StartHurtSemMsg(int _incomingDamage);

	TypeidSystem::TypeID GetTypeID() const override;

	int GetIncomingDamage() const;
};
