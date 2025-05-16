#include "Event/Message/SemanticMsg/StartHurtSemMsg.h"

StartHurtSemMsg::StartHurtSemMsg(int _incomingDamage): incomingDamage(_incomingDamage)
{
}

int StartHurtSemMsg::GetIncomingDamage() const
{
	return incomingDamage;
}

TypeidSystem::TypeID StartHurtSemMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<StartHurtSemMsg>();
}
