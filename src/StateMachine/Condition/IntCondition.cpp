#include "StateMachine/Condition/IntCondition.h"
IntCondition::IntCondition(StateMachine_C::Comparator _comp, ConditionInfo<int>* _value, int _compareTo): OperatorCondition(_comp),
	value_(_value),
	compareTo_(_compareTo)
{
}

IntCondition::IntCondition(ConditionInfo<int>* _value, int _compareTo): value_(_value),
                                                                        compareTo_(_compareTo)
{
}

IntCondition::IntCondition(StateMachine_C::Comparator _comp, ConditionInfo<int>* _value): OperatorCondition(_comp),
	value_(_value)
{
}

IntCondition::IntCondition(ConditionInfo<int>* _value): value_(_value)
{
}

bool IntCondition::Check()
{
	if (!value_)
		return false;

	switch (comp_) {
	case StateMachine_C::Comparator::EQUAL: return value_->value == compareTo_;
	case StateMachine_C::Comparator::NOT_EQUAL: return value_->value != compareTo_;
	case StateMachine_C::Comparator::GREATER: return value_->value > compareTo_;
	case StateMachine_C::Comparator::LESS: return value_->value < compareTo_;
	default:return false;
	}
}

void IntCondition::Set(int _value, int _compareTo, StateMachine_C::Comparator _comp)
{
	if (!value_)
		return;

	value_->value = _value;
	compareTo_ = _compareTo;
	SetComparator(_comp);
}

int IntCondition::GetValue() const
{
	if (!value_)
		return -1;

	return value_->value;
}

int IntCondition::GetCompareTo() const
{
	return compareTo_;
}

TypeidSystem::TypeID IntCondition::GetTypeID() const
{
	return TypeidSystem::GetTypeID<IntCondition>();
}

const IConditionInfo* const IntCondition::GetConditionInfo() const
{
	return value_;
}
