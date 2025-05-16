#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID StartAttackSemMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<StartAttackSemMsg>();
}
