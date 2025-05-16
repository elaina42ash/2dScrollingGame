#pragma once
#include "IFsmCondition.h"

class LeafCondition :public IFsmCondition
{
public:
	~LeafCondition() override = default;
};
