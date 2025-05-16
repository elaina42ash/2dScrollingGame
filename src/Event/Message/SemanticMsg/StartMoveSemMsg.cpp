#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"

#include "Fwk/Framework.h"

StartMoveSemMsg::StartMoveSemMsg(const Lib::Math::Vector2f& _moveInput): moveInput_(_moveInput)
{
}

TypeidSystem::TypeID StartMoveSemMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<StartMoveSemMsg>();
}

Lib::Math::Vector2f StartMoveSemMsg::GetMoveInput() const
{
	return moveInput_;
}
