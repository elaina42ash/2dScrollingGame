#pragma once
#include <memory>

#include "ConditionInfo.h"
#include "LeafCondition.h"

class BoolCondition final :public  LeafCondition
{
private:
	ConditionInfo<bool>* value_;
	bool expected_ = false;

public:
	BoolCondition(ConditionInfo<bool>* _value, bool _expected);

	explicit BoolCondition(ConditionInfo<bool>* _value);

	bool Check() override;

	void Set(bool _value,bool _expected);

	bool GetValue() const;

	bool GetExpected() const;

	TypeidSystem::TypeID GetTypeID() const override;

	const IConditionInfo* const GetConditionInfo() const override;
};
