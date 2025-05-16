#pragma once
#include "CompositeCondition.h"

class AndCondition final :public CompositeCondition
{
public:
	bool Check() override;

	TypeidSystem::TypeID GetTypeID() const override;

	const IConditionInfo* const GetConditionInfo() const override;

	AndCondition* Clone() const;
};
