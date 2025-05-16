#include "StateMachine/State/State.h"

#include "Fwk/Framework.h"

State::State(IStateMachine* _parent,IMessenger* _messenger): parent_(_parent),messenger_(_messenger)
{
}

void State::Enter()
{
	isExited_ = false;

	timer_.Reset();
}

void State::Update()
{
	timer_.Update(Time_I->GetDeltaTime());
}

void State::Exit()
{
	isExited_ = true;

	timer_.Reset();
}

void State::SetParent(IStateMachine* _parent)
{
	parent_.Bind(_parent);
}

const IStateMachine* State::GetParent() const
{
	return parent_.Injected();
}

bool State::IsExited() const
{
	return isExited_;
}

void State::SendMsg(const IEventMessage& _message) const
{
	messenger_->SendMsg(_message);
}
