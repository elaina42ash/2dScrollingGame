#include "StateMachine/Condition/OperatorCondition.h"

OperatorCondition::OperatorCondition(StateMachine_C::Comparator _comp): comp_(_comp)
{
}

OperatorCondition::OperatorCondition(): comp_(StateMachine_C::Comparator::EQUAL)
{
}

void OperatorCondition::SetComparator(StateMachine_C::Comparator _comp)
{
	comp_ = _comp;
}

StateMachine_C::Comparator OperatorCondition::GetComparator() const
{
	return comp_;
}
