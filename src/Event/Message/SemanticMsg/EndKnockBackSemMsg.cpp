#include "Event/Message/SemanticMsg/EndKnockBackSemMsg.h"
#include "TypeID.h"

TypeidSystem::TypeID EndKnockBackSemMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<EndKnockBackSemMsg>();
}
