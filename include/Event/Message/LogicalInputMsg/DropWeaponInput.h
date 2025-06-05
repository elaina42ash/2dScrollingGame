#pragma once
#include "Event/Message/IEventMessage.h"

class DropWeaponInput : public IEventMessage
{
public:
	TypeidSystem::TypeID GetTypeID() const override;
};
