#include "Event/Message/LogicalInputMsg/DashInputMsg.h"

TypeidSystem::TypeID DashInputMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<DashInputMsg>();
}
