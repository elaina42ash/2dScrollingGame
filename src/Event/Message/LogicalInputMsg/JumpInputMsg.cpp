#include "Event/Message/LogicalInputMsg/JumpInputMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID JumpInputMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<JumpInputMsg>();
}
