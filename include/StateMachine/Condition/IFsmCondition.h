#pragma once
#include <memory>

#include "IConditionInfo.h"
#include "TypeID.h"

// 条件接口：用于判断是否允许状态切换
class IFsmCondition : public TypeidSystem::ITypeID
{
public:
	~IFsmCondition() override = default;

	virtual bool Check() = 0;

	virtual const IConditionInfo* const GetConditionInfo() const = 0;

};