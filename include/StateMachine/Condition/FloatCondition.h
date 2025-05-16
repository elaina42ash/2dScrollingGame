#pragma once
#include <memory>

#include "ConditionInfo.h"
#include "OperatorCondition.h"

class FloatCondition final : public OperatorCondition
{
private:

	ConditionInfo<float>* value_;
	float compareTo_ =0.0f;

public:
	FloatCondition(StateMachine_C::Comparator _comp, ConditionInfo<float>* _value, float _compareTo);

	FloatCondition(ConditionInfo<float>* _value, float _compareTo);

	FloatCondition(StateMachine_C::Comparator _comp, ConditionInfo<float>* _value);

	explicit FloatCondition(ConditionInfo<float>* _value);

	bool Check() override;

	void Set(float _value, float _compareTo, StateMachine_C::Comparator _comp);

	float GetValue() const;

	float GetCompareTo() const;

	TypeidSystem::TypeID GetTypeID() const override;

	const IConditionInfo* const GetConditionInfo() const override;
};
