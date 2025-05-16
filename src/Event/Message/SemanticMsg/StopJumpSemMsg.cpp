#include "Event/Message/SemanticMsg/StopJumpSemMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID StopJumpSemMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<StopJumpSemMsg>();
}
