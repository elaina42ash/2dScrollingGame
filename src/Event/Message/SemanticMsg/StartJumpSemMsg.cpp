#include "Event/Message/SemanticMsg/StartJumpSemMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID StartJumpSemMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<StartJumpSemMsg>();
}
