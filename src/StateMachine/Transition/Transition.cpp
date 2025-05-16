#include "StateMachine/Transition/Transition.h"

Transition::Transition(int _from, int _to, AndCondition* _condition, const std::function<void()>& _action): from_(_from),
	to_(_to),
	condition_(_condition),
	action_(_action)
{
}

Transition::~Transition()
{
	if (condition_)
	{
		delete condition_;
		condition_ = nullptr;
	}
}

Transition::Transition(const Transition& _other): from_(_other.from_),
                                                  to_(_other.to_),
                                                  action_(_other.action_)
{
	condition_ = _other.condition_ ? _other.condition_->Clone() : nullptr;
}

Transition::Transition(Transition&& _other) noexcept: from_(_other.from_),
                                                      to_(_other.to_),
                                                      condition_(_other.condition_),
                                                      action_(std::move(_other.action_))
{
	_other.condition_ = nullptr;
}

Transition& Transition::operator=(const Transition& _other)
{
	if (this == &_other)
		return *this;

	from_ = _other.from_;
	to_ = _other.to_;
	action_ = _other.action_;

	if (condition_)
	{
		delete condition_;
		condition_ = nullptr;
	}

	condition_ = _other.condition_ ? _other.condition_->Clone() : nullptr;

	return *this;
}

Transition& Transition::operator=(Transition&& _other) noexcept
{
	if (this == &_other)
		return *this;
	from_ = _other.from_;
	to_ = _other.to_;
	action_ = std::move(_other.action_);

	if (condition_)
	{
		delete condition_;
		condition_ = nullptr;
	}

	condition_ = _other.condition_;

	_other.condition_ = nullptr;

	return *this;
}
