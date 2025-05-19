#pragma once
#include "Event/Message/IEventMessage.h"

class StartSwitchWeaponSemMsg : IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
