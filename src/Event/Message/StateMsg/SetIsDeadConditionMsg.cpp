#include "Event/Message/StateMsg/SetIsDeadConditionMsg.h"

SetIsDeadConditionMsg::SetIsDeadConditionMsg(bool _value):value_(_value)
{
		
}

bool SetIsDeadConditionMsg::GetValue() const
{
	return value_;
}

TypeidSystem::TypeID SetIsDeadConditionMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<SetIsDeadConditionMsg>();
}
