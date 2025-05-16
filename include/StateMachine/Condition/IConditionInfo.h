#pragma once
#include "StateMachine/StateMachineDef.h"

struct IConditionInfo
{
	virtual  ~IConditionInfo() = default;

	virtual StateMachine_C::ParameterType GetType() const =0;

	virtual bool GetBoolValue() const = 0;

	virtual int GetIntValue() const = 0;

	virtual float GetFloatValue() const = 0;
};
