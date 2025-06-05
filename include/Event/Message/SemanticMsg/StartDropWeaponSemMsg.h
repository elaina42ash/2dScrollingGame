#pragma once
#include "Event/Message/IEventMessage.h"

class StartDropWeaponSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
