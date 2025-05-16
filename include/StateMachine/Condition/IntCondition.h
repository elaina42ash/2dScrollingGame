#pragma once
#include <memory>

#include "ConditionInfo.h"
#include "OperatorCondition.h"

class IntCondition final : public OperatorCondition
{
private:
	ConditionInfo<int>* value_;
	int compareTo_ =0;

public:
	IntCondition(StateMachine_C::Comparator _comp, ConditionInfo<int>* _value, int _compareTo);

	IntCondition(ConditionInfo<int>* _value, int _compareTo);

	IntCondition(StateMachine_C::Comparator _comp, ConditionInfo<int>* _value);

	explicit IntCondition(ConditionInfo<int>* _value);

	bool Check() override;

	void Set(int _value, int _compareTo, StateMachine_C::Comparator _comp);

	int GetValue() const;

	int GetCompareTo() const;

	TypeidSystem::TypeID GetTypeID() const override;

	const IConditionInfo* const GetConditionInfo() const override;
};
