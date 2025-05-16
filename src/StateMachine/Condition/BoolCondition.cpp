#include "StateMachine/Condition/BoolCondition.h"
BoolCondition::BoolCondition(ConditionInfo<bool>* _value, bool _expected): value_(_value),
                                                                           expected_(_expected)
{
}

BoolCondition::BoolCondition(ConditionInfo<bool>* _value): value_(_value)
{
}

bool BoolCondition::Check()
{
	if (!value_)
		return false;

	return value_->value == expected_;
}

void BoolCondition::Set(bool _value, bool _expected)
{
	value_->value = _value;
	expected_ = _expected;
}

bool BoolCondition::GetValue() const
{
	if (!value_)
		return false;

	return value_->value;
}

bool BoolCondition::GetExpected() const
{
	return expected_;
}

TypeidSystem::TypeID BoolCondition::GetTypeID() const
{
	return TypeidSystem::GetTypeID<BoolCondition>();
}

const IConditionInfo* const BoolCondition::GetConditionInfo() const
{
	return value_;
}
