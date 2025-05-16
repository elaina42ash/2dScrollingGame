#include "Event/Message/StateMsg/EnterIdleStateMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID EnterIdleStateMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<EnterIdleStateMsg>();
}
