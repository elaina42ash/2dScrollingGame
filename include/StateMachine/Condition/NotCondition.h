#pragma once
#include "IFsmCondition.h"


class NotCondition final :public IFsmCondition
{
private:
	IFsmCondition* condition_ = nullptr;

public:
	explicit NotCondition(IFsmCondition* _condition);

	bool Check() override;

	TypeidSystem::TypeID GetTypeID() const override;

	const IConditionInfo* const GetConditionInfo() const override;
};
