#include "Event/Message/StateMsg/SetIsClearConditionMsg.h"

SetIsClearConditionMsg::SetIsClearConditionMsg(bool _value): value_(_value)
{
		
}

bool SetIsClearConditionMsg::GetValue() const
{
	return value_;
}

TypeidSystem::TypeID SetIsClearConditionMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<SetIsClearConditionMsg>();
}
