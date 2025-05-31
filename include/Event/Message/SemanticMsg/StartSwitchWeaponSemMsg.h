#pragma once
#include "Event/Message/IEventMessage.h"

class StartSwitchWeaponSemMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
