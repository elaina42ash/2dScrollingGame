#include "Event/Message/SemanticMsg/StartIdleSemMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID StartIdleSemMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<StartIdleSemMsg>();
}
