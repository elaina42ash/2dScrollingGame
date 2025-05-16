#pragma once
#include "CompositeCondition.h"

class OrCondition final :public CompositeCondition
{
public:
	bool Check() override;

	TypeidSystem::TypeID GetTypeID() const override;

	const IConditionInfo* const GetConditionInfo() const override;
};
