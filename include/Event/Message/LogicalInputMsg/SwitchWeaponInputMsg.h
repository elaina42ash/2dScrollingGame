#pragma once
#include "Event/Message/IEventMessage.h"

class SwitchWeaponInputMsg : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
