#pragma once
#include <stdexcept>
#include "IConditionInfo.h"

template <typename T>
struct ConditionInfo : IConditionInfo
{
	T value;

	StateMachine_C::ParameterType type;

	ConditionInfo(const T& _value, StateMachine_C::ParameterType _type)
		: value(_value),
		  type(_type)
	{
	}

	~ConditionInfo() override = default;

	StateMachine_C::ParameterType GetType() const override
	{
		return type;
	}

	T GetValue() const
	{
		return value;
	}

	bool GetBoolValue() const override
	{
		if (type== StateMachine_C::ParameterType::BOOL)
		{
			return GetValue();
		}
		else
		{
			throw std::logic_error("ConditionInfo<T>::GetFloatValue: T is not bool");
		}
	
	}

	int GetIntValue() const override
	{
		if (type == StateMachine_C::ParameterType::INT)
		{
			return GetValue();
		}
		else
		{
			throw std::logic_error("ConditionInfo<T>::GetFloatValue: T is not int");
		}
	}

	float GetFloatValue() const override
	{
		if (type == StateMachine_C::ParameterType::FLOAT)
		{
			return GetValue();
		}
		else
		{
			throw std::logic_error("ConditionInfo<T>::GetFloatValue: T is not float");
		}
	}
};
