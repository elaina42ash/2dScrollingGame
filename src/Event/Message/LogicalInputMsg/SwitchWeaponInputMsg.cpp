#include "Event/Message/LogicalInputMsg/SwitchWeaponInputMsg.h"

TypeidSystem::TypeID SwitchWeaponInputMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<SwitchWeaponInputMsg>();
}
