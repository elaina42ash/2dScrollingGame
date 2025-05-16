#include "StateMachine/Condition/FloatCondition.h"
#include <cmath>
FloatCondition::FloatCondition(StateMachine_C::Comparator _comp, ConditionInfo<float>* _value, float _compareTo): OperatorCondition(_comp),
	value_(_value),
	compareTo_(_compareTo)
{
}

FloatCondition::FloatCondition(ConditionInfo<float>* _value, float _compareTo): value_(_value),
	compareTo_(_compareTo)
{
}

FloatCondition::FloatCondition(StateMachine_C::Comparator _comp, ConditionInfo<float>* _value): OperatorCondition(_comp),
	value_(_value)
{
}

FloatCondition::FloatCondition(ConditionInfo<float>* _value): value_(_value)
{
}

bool FloatCondition::Check()
{
	if (!value_)
		return false;

	constexpr float epsilon = 0.0000001f;
	switch (comp_) {
	case StateMachine_C::Comparator::EQUAL: return std::fabs(value_->value - compareTo_) < epsilon;
	case StateMachine_C::Comparator::NOT_EQUAL: return std::fabs(value_->value - compareTo_) >= epsilon;
	case StateMachine_C::Comparator::GREATER: return value_->value > compareTo_;
	case StateMachine_C::Comparator::LESS: return value_->value < compareTo_;
	default:return false;
	}
}

void FloatCondition::Set(float _value, float _compareTo, StateMachine_C::Comparator _comp)
{
	if (!value_)
		return;

	value_->value = _value;
	compareTo_ = _compareTo;
	SetComparator(_comp);
}

float FloatCondition::GetValue() const
{
	if (!value_)
		return 0.0f;

	return value_->value;
}

float FloatCondition::GetCompareTo() const
{
	return compareTo_;
}

TypeidSystem::TypeID FloatCondition::GetTypeID() const
{
	return TypeidSystem::GetTypeID<FloatCondition>();
}

const IConditionInfo* const FloatCondition::GetConditionInfo() const
{
	return value_;
}
