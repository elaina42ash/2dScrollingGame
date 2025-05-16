#pragma once
#include <vector>

#include "IFsmCondition.h"


class CompositeCondition:public IFsmCondition
{
protected:
	std::vector<IFsmCondition*> children_;

public:
	~CompositeCondition() override;

	void Add(IFsmCondition* _condition);

	void Remove(IFsmCondition* _condition);

	IFsmCondition* FindByConditionInfo(const IConditionInfo* _condInfo) const;
};

