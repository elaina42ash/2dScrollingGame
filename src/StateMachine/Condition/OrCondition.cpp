#include "StateMachine/Condition/OrCondition.h"

bool OrCondition::Check()
{
	for (auto* cond:children_)
	{
		if (cond && cond->Check())
			return true;
	}
	return false;
}

TypeidSystem::TypeID OrCondition::GetTypeID() const
{
	return TypeidSystem::GetTypeID<OrCondition>();
}

const IConditionInfo* const OrCondition::GetConditionInfo() const
{
	return nullptr;
}
