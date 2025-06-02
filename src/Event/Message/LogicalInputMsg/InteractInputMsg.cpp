#include "Event/Message/LogicalInputMsg/InteractInputMsg.h"

TypeidSystem::TypeID InteractInputMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<InteractInputMsg>();
}
