#include "Event/Message/LogicalInputMsg/HoriAxisInputMsg.h"
HoriAxisInputMsg::HoriAxisInputMsg(float _value): value_(_value)
{
}

TypeidSystem::TypeID HoriAxisInputMsg::GetTypeID() const
{
	return TypeidSystem::GetTypeID<HoriAxisInputMsg>();
}

float HoriAxisInputMsg::GetValue() const
{
	return value_;
}
