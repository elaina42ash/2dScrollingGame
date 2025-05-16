#include "StateMachine/Condition/CompositeCondition.h"
#include <ostream>

CompositeCondition::~CompositeCondition()
{
	for (auto* cond : children_) {
		if (cond)
		{
			delete cond;
			cond = nullptr;
		}

	}
	children_.clear();
}

void CompositeCondition::Add(IFsmCondition* _condition)
{
	if (std::find(children_.begin(), children_.end(), _condition) == children_.end())
		children_.push_back(_condition);
}

void CompositeCondition::Remove(IFsmCondition* _condition)
{
	children_.erase(std::remove(children_.begin(), children_.end(), _condition), children_.end());
}

IFsmCondition* CompositeCondition::FindByConditionInfo(const IConditionInfo* _condInfo) const
{
	if (_condInfo == nullptr)
		return nullptr;

	for (auto it = children_.begin(); it != children_.end(); ++it)
	{
		if ((*it)->GetConditionInfo() == _condInfo)
			return *it;
	}

	return nullptr;
}
