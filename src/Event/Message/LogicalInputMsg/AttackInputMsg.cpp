#include "Event/Message/LogicalInputMsg/AttackInputMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID AttackInputMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<AttackInputMsg>();
}
