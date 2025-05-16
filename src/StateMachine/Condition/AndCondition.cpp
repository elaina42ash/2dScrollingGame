#include "StateMachine/Condition/AndCondition.h"

bool AndCondition::Check()
{
	for (const auto& cond:children_)
	{
		if (!cond||!cond->Check())
			return false;
	}
	return true;
}

TypeidSystem::TypeID AndCondition::GetTypeID() const
{
	return TypeidSystem::GetTypeID<AndCondition>();
}

const IConditionInfo* const AndCondition::GetConditionInfo() const
{
	return nullptr;
}

AndCondition* AndCondition::Clone() const
{
	return new AndCondition(*this);
}
