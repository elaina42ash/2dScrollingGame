#include "StateMachine/Condition/NotCondition.h"

NotCondition::NotCondition(IFsmCondition* _condition): condition_(_condition)
{
}

bool NotCondition::Check()
{
	return condition_ ? !condition_->Check() : false;
}

TypeidSystem::TypeID NotCondition::GetTypeID() const
{
	return TypeidSystem::GetTypeID<NotCondition>();
}

const IConditionInfo* const NotCondition::GetConditionInfo() const
{
	return nullptr;
}
