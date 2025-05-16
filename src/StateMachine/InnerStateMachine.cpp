#include "StateMachine/InnerStateMachine.h"

InnerStateMachine::InnerStateMachine(IStateMachine* _parent, IMessenger* _messenger) : State(_parent, _messenger)
{
	innerFsm_ = new StateMachine;
}

InnerStateMachine::~InnerStateMachine()
{
	if (innerFsm_)
	{
		delete innerFsm_;
		innerFsm_ = nullptr;
	}
}

void InnerStateMachine::Enter()
{
	State::Enter();
}

void InnerStateMachine::Update()
{
	State::Update();

	if (innerFsm_->IsStateMachineExited())
	{
		this->Exit();

		return;
	}

	innerFsm_->Update();
}

void InnerStateMachine::Exit()
{
	State::Exit();
}

void InnerStateMachine::AddState(const StateID _id, IState* _state)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddState(_id, _state);
}

void InnerStateMachine::RemoveState(const StateID _id)
{
	if (!innerFsm_)
		return;

	innerFsm_->RemoveState(_id);
}

int InnerStateMachine::CurrentStateId() const
{
	if (!innerFsm_)
		return -1;

	return innerFsm_->CurrentStateId();
}

void InnerStateMachine::AddTransition(const StateID _from, const StateID _to)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddTransition(_from, _to);
}

void InnerStateMachine::RemoveTransition(const StateID _from, const StateID _to)
{
	if (!innerFsm_)
		return;

	innerFsm_->RemoveTransition(_from, _to);
}

void InnerStateMachine::AddTransitionFromAny(StateID _to)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddTransitionFromAny(_to);
}

void InnerStateMachine::AddConditionToTransition(const ConditionID _id, const StateID _from, const StateID _to)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddConditionToTransition(_id, _from, _to);
}

void InnerStateMachine::AddConditionToAnyTransition(ConditionID _conditionID, StateID _to)
{
	if (!innerFsm_)
		return;
	innerFsm_->AddConditionToAnyTransition(_conditionID, _to);
}

void InnerStateMachine::AddConditionToExitTransition(ConditionID _conditionID, StateID _from)
{
	if (!innerFsm_)
		return;
	innerFsm_->AddConditionToExitTransition(_conditionID, _from);
}

void InnerStateMachine::RemoveConditionFromTransition(const ConditionID _id, const StateID _from,
	const StateID _to)
{
	if (!innerFsm_)
		return;

	innerFsm_->RemoveConditionFromTransition(_id, _from, _to);
}

void InnerStateMachine::AddActionToTransition(const std::function<void()>& _action, const StateID _from,
	const StateID _to)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddActionToTransition(_action, _from, _to);
}

void InnerStateMachine::RemoveActionFromTransition(const StateID _from, const StateID _to)
{
	if (!innerFsm_)
		return;

	innerFsm_->RemoveActionFromTransition(_from, _to);
}

void InnerStateMachine::SetInitialState(const StateID _id)
{
	if (!innerFsm_)
		return;

	innerFsm_->SetInitialState(_id);
}

void InnerStateMachine::AddBoolConditionInfo(const ConditionID _id, const bool _value)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddBoolConditionInfo(_id, _value);
}

void InnerStateMachine::AddFloatConditionInfo(const ConditionID _id, const float _value)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddFloatConditionInfo(_id, _value);
}

void InnerStateMachine::AddIntConditionInfo(const ConditionID _id, const int _value)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddIntConditionInfo(_id, _value);
}

void InnerStateMachine::RemoveCondition(const ConditionID _id)
{
	if (!innerFsm_)
		return;

	innerFsm_->RemoveCondition(_id);
}

void InnerStateMachine::SetBoolConditionInfo(const ConditionID _id, const bool _value)
{
	if (!innerFsm_)
		return;

	innerFsm_->SetBoolConditionInfo(_id, _value);
}

void InnerStateMachine::SetFloatConditionInfo(const ConditionID _id, const float _value)
{
	if (!innerFsm_)
		return;

	innerFsm_->SetFloatConditionInfo(_id, _value);
}

void InnerStateMachine::SetIntConditionInfo(const ConditionID _id, const int _value)
{
	if (!innerFsm_)
		return;

	innerFsm_->SetIntConditionInfo(_id, _value);
}

void InnerStateMachine::SetBoolCondition(const ConditionID _id, const StateID _from, const StateID _to, const bool _expected)
{
	if (!innerFsm_)
		return;

	innerFsm_->SetBoolCondition(_id, _from, _to, _expected);
}

void InnerStateMachine::SetFloatCondition(const ConditionID _id, StateID _from,
	StateID _to, const float _compareTo, const StateMachine_C::Comparator& _comp)
{
	if (!innerFsm_)
		return;

	innerFsm_->SetFloatCondition(_id, _from, _to, _compareTo, _comp);
}

void InnerStateMachine::SetIntCondition(const ConditionID _id, StateID _from,
	StateID _to, const int _compareTo, const StateMachine_C::Comparator& _comp)
{
	if (!innerFsm_)
		return;

	innerFsm_->SetIntCondition(_id, _from, _to, _compareTo, _comp);
}

void InnerStateMachine::SetBoolConditionForAnyTransition(ConditionID _id, StateID _to, bool _expected)
{
	if (!innerFsm_)
		return;
	innerFsm_->SetBoolConditionForAnyTransition(_id, _to, _expected);
}

void InnerStateMachine::SetBoolConditionForExitTransition(ConditionID _id, StateID _from, bool _expected)
{
	if (!innerFsm_)
		return;
	innerFsm_->SetBoolConditionForExitTransition(_id, _from, _expected);
}

void InnerStateMachine::SetFloatConditionForAnyTransition(ConditionID _id, StateID _to, float _compareTo,
	const StateMachine_C::Comparator& _comp)
{
	if (!innerFsm_)
		return;
	innerFsm_->SetFloatConditionForAnyTransition(_id, _to, _compareTo, _comp);
}

void InnerStateMachine::SetFloatConditionForExitTransition(ConditionID _id, StateID _from, float _compareTo,
	const StateMachine_C::Comparator& _comp)
{
	if (!innerFsm_)
		return;
	innerFsm_->SetFloatConditionForExitTransition(_id, _from, _compareTo, _comp);
}

void InnerStateMachine::SetIntConditionForAnyTransition(ConditionID _id, StateID _to, int _compareTo,
	const StateMachine_C::Comparator& _comp)
{
	if (!innerFsm_)
		return;
	innerFsm_->SetIntConditionForAnyTransition(_id, _to, _compareTo, _comp);
}

void InnerStateMachine::SetIntConditionForExitTransition(ConditionID _id, StateID _from, int _compareTo,
	const StateMachine_C::Comparator& _comp)
{
	if (!innerFsm_)
		return;
	innerFsm_->SetIntConditionForExitTransition(_id, _from, _compareTo, _comp);
}

const IConditionInfo* InnerStateMachine::GetConditionInfo(const ConditionID _conditionID) const
{
	if (!innerFsm_)
		return nullptr;

	return innerFsm_->GetConditionInfo(_conditionID);
}

const IFsmCondition* InnerStateMachine::GetCondition(const ConditionID _conditionID, const StateID _from,
                                                     const StateID _to) const
{
	if (!innerFsm_)
		return nullptr;

	return innerFsm_->GetCondition(_conditionID, _from, _to);
}

void InnerStateMachine::ReceiveInput(void(*_inputHandle)(IStateMachine&))
{
	if (!innerFsm_)
		return;

	innerFsm_->ReceiveInput(_inputHandle);
}

void InnerStateMachine::AddTransitionToExit(const StateID _from)
{
	if (!innerFsm_)
		return;

	innerFsm_->AddTransitionToExit(_from);
}

bool InnerStateMachine::IsStateMachineExited() const
{
	if (!innerFsm_)
		return false;

	return innerFsm_->IsStateMachineExited();
}

IStateMachine* InnerStateMachine::AsStateMachine()
{
	return this;
}

void InnerStateMachine::ResetStateMachine()
{
	if (!innerFsm_)
		return;
	innerFsm_->ResetStateMachine();
}

bool InnerStateMachine::IsEmpty() const
{
	if (!innerFsm_)
		return true;
	return innerFsm_->IsEmpty();
}

IStateMachine::StateID InnerStateMachine::GetExitStateID() const
{
	if (!innerFsm_)
		return GetNoneStateID();

	return innerFsm_->GetExitStateID();
}

IStateMachine::StateID InnerStateMachine::GetAnyStateID() const
{
	if (!innerFsm_)
		return GetNoneStateID();

	return innerFsm_->GetAnyStateID();
}

IStateMachine::StateID InnerStateMachine::GetNoneStateID() const
{
	if (!innerFsm_)
		return INT_MIN;

	return innerFsm_->GetNoneStateID();
}
