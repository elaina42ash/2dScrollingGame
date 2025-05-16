#include "Event/Message/LogicalInputMsg/ReleaseJumpInputMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID ReleaseJumpInputMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<ReleaseJumpInputMsg>();
}
