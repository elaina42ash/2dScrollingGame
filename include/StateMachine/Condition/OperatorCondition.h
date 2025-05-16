#pragma once
#include "LeafCondition.h"
#include "StateMachine/StateMachineDef.h"

class OperatorCondition : public LeafCondition
{
public:
	explicit OperatorCondition(StateMachine_C::Comparator _comp);

	explicit OperatorCondition();

protected:
	StateMachine_C::Comparator comp_ = StateMachine_C::Comparator::NONE;

public:
	void SetComparator(StateMachine_C::Comparator _comp);
	StateMachine_C::Comparator GetComparator() const;
};
