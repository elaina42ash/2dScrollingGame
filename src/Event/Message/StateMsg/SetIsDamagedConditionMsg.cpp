#include "Event/Message/StateMsg/SetIsDamagedConditionMsg.h"

SetIsDamagedConditionMsg::SetIsDamagedConditionMsg(bool _value): value_(_value)
{
}

bool SetIsDamagedConditionMsg::GetValue() const
{
	return value_;
}

TypeidSystem::TypeID SetIsDamagedConditionMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<SetIsDamagedConditionMsg>();
}
