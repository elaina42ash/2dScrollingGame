#include "StateMachine/StateMachine.h"
#include <iostream>
#include <string>

#include "Fwk/Framework.h"
#include "StateMachine/Condition/AndCondition.h"
#include "StateMachine/Condition/BoolCondition.h"
#include "StateMachine/Condition/FloatCondition.h"
#include "StateMachine/Condition/IntCondition.h"
#include "StateMachine/State/IState.h"
StateMachine::StateMachine()
{
	currentState_ = nullptr;
}

StateMachine::~StateMachine()
{
	for (auto& pair : conditionMap_)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}

	conditionMap_.clear();
}

void StateMachine::ChangeState(StateID _id)
{
	auto it = stateMap_.find(_id);

	if (it == stateMap_.end())
		return;

	if (it->second == currentState_)
		return;

	if (currentState_)
		currentState_->Exit();

	currentState_ = it->second;
	currentStateID_ = it->first;

	currentState_->Enter();
}

void StateMachine::ValidateUserStateID(StateID _id) const
{
	if (_id < MIN_USER_STATE_ID) {
		throw std::invalid_argument(" Error: Reserved StateID " + std::to_string(_id) + " is not allowed.");
	}
}

void StateMachine::AddTransitionNoSafeCheck(StateID _from, StateID _to)
{
	auto it = std::find_if(transitions_.begin(), transitions_.end(), [_from, _to](const Transition& t)
		{
			return _from == t.from_ && _to == t.to_;
		});

	if (it != transitions_.end())
		return;

	transitions_.emplace_back(_from, _to, new AndCondition(), nullptr);
}

void StateMachine::AddConditionToTransitionNoSafeCheck(ConditionID _id, StateID _from, StateID _to)
{
	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return;

	IConditionInfo* condInfo = it->second;

	for (auto& t : transitions_)
	{
		if (t.from_ != _from || t.to_ != _to)
			continue;

		if (!t.condition_)
			t.condition_ = new AndCondition();

		AndCondition* andCond = t.condition_;

		if (!andCond)
			continue;

		if (andCond->FindByConditionInfo(condInfo))
			return;

		switch (condInfo->GetType())
		{
		case StateMachine_C::ParameterType::BOOL:
		{
			andCond->Add(new BoolCondition(dynamic_cast<ConditionInfo<bool>*>(condInfo)));
		}
		break;
		case StateMachine_C::ParameterType::INT:
		{
			andCond->Add(new IntCondition(dynamic_cast<ConditionInfo<int>*>(condInfo)));
		}
		break;
		case StateMachine_C::ParameterType::FLOAT:
		{
			andCond->Add(new FloatCondition(dynamic_cast<ConditionInfo<float>*>(condInfo)));
		}
		break;
		default:
		{
			throw std::logic_error("[FSM] AddConditionToTransition: Unknown ParameterType encountered.");
		}
		}
	}
}

void StateMachine::SetBoolConditionNoSafeCheck(ConditionID _id, IStateMachine::StateID _from,
	IStateMachine::StateID _to, bool _expected)
{
	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return;

	const IConditionInfo* condInfo = it->second;

	for (auto& t : transitions_)
	{
		if (!(t.from_ == _from && t.to_ == _to))
			continue;

		if (!t.condition_)
			continue;

		AndCondition* andCond = t.condition_;

		BoolCondition* conditionToSet = dynamic_cast<BoolCondition*>(andCond->FindByConditionInfo(condInfo));

		if (!conditionToSet)
			continue;

		conditionToSet->Set(conditionToSet->GetValue(), _expected);
	}
}

void StateMachine::SetFloatConditionNoSafeCheck(ConditionID _id, IStateMachine::StateID _from,
	IStateMachine::StateID _to, float _compareTo, const StateMachine_C::Comparator& _comp)
{
	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return;

	const IConditionInfo* condInfo = it->second;

	for (auto& t : transitions_)
	{
		if (!(t.from_ == _from && t.to_ == _to))
			continue;

		if (!t.condition_)
			continue;

		AndCondition* andCond = t.condition_;

		if (!andCond)
			continue;

		FloatCondition* conditionToSet = dynamic_cast<FloatCondition*>(andCond->FindByConditionInfo(condInfo));
		if (!conditionToSet)
			continue;

		conditionToSet->Set(conditionToSet->GetValue(), _compareTo, _comp);
	}
}

void StateMachine::SetIntConditionNoSafeCheck(ConditionID _id, IStateMachine::StateID _from, IStateMachine::StateID _to,
	int _compareTo, const StateMachine_C::Comparator& _comp)
{
	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return;

	const IConditionInfo* condInfo = it->second;

	for (auto& t : transitions_)
	{
		if (!(t.from_ == _from && t.to_ == _to))
			continue;

		if (!t.condition_)
			continue;

		AndCondition* andCond = t.condition_;

		if (!andCond)
			continue;

		IntCondition* conditionToSet = dynamic_cast<IntCondition*>(andCond->FindByConditionInfo(condInfo));

		if (!conditionToSet)
			continue;

		conditionToSet->Set(conditionToSet->GetValue(), _compareTo, _comp);
	}
}


void StateMachine::AddState(StateID _id, IState* _state)
{
	ValidateUserStateID(_id);

	if (stateMap_.count(_id) > 0)
	{
		throw std::logic_error("[FSM] State already registered.");
	}

	stateMap_[_id] = _state;
}

void StateMachine::RemoveState(StateID _id)
{
	ValidateUserStateID(_id);

	auto pairIt = stateMap_.find(_id);

	if (pairIt == stateMap_.end())
		return;

	if (pairIt->second == currentState_)
	{
		currentState_->Exit();
		currentState_ = nullptr;
	}

	RemoveTransitionAssociatedWith(_id);

	stateMap_.erase(pairIt);
}

void StateMachine::AddTransition(StateID _from, StateID _to)
{
	AddTransitionNoSafeCheck(_from, _to);
}

void StateMachine::RemoveTransition(StateID _from, StateID _to)
{
	ValidateUserStateID(_from);

	ValidateUserStateID(_to);

	for (auto it = transitions_.begin(); it != transitions_.end(); ++it) {
		if (!(it->from_ == _from && it->to_ == _to))
			continue;

		transitions_.erase(it);
		break;
	}
}

void StateMachine::RemoveTransitionAssociatedWith(StateID _id)
{
	ValidateUserStateID(_id);

	for (auto it = transitions_.begin(); it != transitions_.end(); ) {
		if (!(it->from_ == _id || it->to_ == _id))
		{
			++it;

			continue;
		}

		it = transitions_.erase(it);
	}
}

void StateMachine::AddTransitionToExit(StateID _from)
{
	AddTransitionNoSafeCheck(_from, EXIT_STATE_ID);
}

void StateMachine::AddTransitionFromAny(StateID _to)
{
	AddTransitionNoSafeCheck(ANY_STATE_ID, _to);
}

void StateMachine::SetInitialState(StateID _id)
{
	ValidateUserStateID(_id);

	auto it = stateMap_.find(_id);

	if (it == stateMap_.end())
		return;

	initialStateID_ = it->first;
	initialState_ = it->second;

	ChangeState(initialStateID_);
}

void StateMachine::ChangeStateToExit()
{
	currentState_->Exit();

	currentState_ = nullptr;
	currentStateID_ = NONE;
}

bool StateMachine::TryExecuteTransitionFrom(int _from)
{
	for (size_t i = 0; i < transitions_.size(); i++)
	{
		const Transition& t = transitions_[i];

		if (t.from_ != _from)
			continue;

		if (currentStateID_== t.to_)
			continue;

		if (!t.condition_)
			throw std::logic_error("Transition condition is null");

		if (!t.condition_->Check())
			continue;

		if (t.action_)
			t.action_();

		if (t.to_ == EXIT_STATE_ID)
			ChangeStateToExit();
		else
			ChangeState(t.to_);

		return true;
	}
	return false;
}

void StateMachine::Update()
{
	if (!currentState_)
		return;

	bool stateChanged = TryExecuteTransitionFrom(currentStateID_);

	if (!stateChanged)
		stateChanged = TryExecuteTransitionFrom(ANY_STATE_ID);

	//if (stateChanged)
	//	DebugLog(to_string(CurrentStateId()));

	if (!stateChanged && !currentState_->IsExited())
		currentState_->Update();

}

int StateMachine::CurrentStateId() const
{
	if (!currentState_)
		return -1;

	return currentStateID_;
}

void StateMachine::AddConditionToTransition(ConditionID _id, StateID _from, StateID _to)
{
	AddConditionToTransitionNoSafeCheck(_id, _from, _to);
}

void StateMachine::AddConditionToAnyTransition(ConditionID _conditionID, StateID _to)
{
	AddConditionToTransitionNoSafeCheck(_conditionID, ANY_STATE_ID, _to);
}

void StateMachine::AddConditionToExitTransition(ConditionID _conditionID, StateID _from)
{
	AddConditionToTransitionNoSafeCheck(_conditionID, _from, EXIT_STATE_ID);
}


void StateMachine::RemoveConditionFromTransition(ConditionID _id, StateID _from, StateID _to)
{
	ValidateUserStateID(_from);

	ValidateUserStateID(_to);

	for (auto& t : transitions_)
	{
		if (t.from_ != _from || t.to_ != _to)
			continue;

		if (!t.condition_)
			continue;

		AndCondition* andCond = t.condition_;

		if (!andCond)
			continue;

		auto it = conditionMap_.find(_id);

		if (it == conditionMap_.end())
			continue;

		IConditionInfo* targetConditionInfo = it->second;

		IFsmCondition* targetCondition = andCond->FindByConditionInfo(targetConditionInfo);

		if (!targetCondition)
			continue;

		andCond->Remove(targetCondition);

		break; // 只处理第一个匹配的 from→to 跳转
	}
}

void StateMachine::AddActionToTransition(const std::function<void()>& _action, StateID _from, StateID _to)
{
	ValidateUserStateID(_from);

	ValidateUserStateID(_to);

	for (auto& t : transitions_)
	{
		if (t.from_ == _from && t.to_ == _to)
		{
			t.action_ = _action;
		}
	}
}

void StateMachine::RemoveActionFromTransition(StateID _from, StateID _to)
{
	ValidateUserStateID(_from);

	ValidateUserStateID(_to);

	for (auto& t : transitions_)
	{
		if (t.from_ == _from && t.to_ == _to)
		{
			t.action_ = nullptr;
		}
	}
}

void StateMachine::AddBoolConditionInfo(ConditionID _id, bool _value)
{

	conditionMap_[_id] = new ConditionInfo<bool>(_value, StateMachine_C::ParameterType::BOOL);
}

void StateMachine::AddFloatConditionInfo(ConditionID _id, float _value)
{
	conditionMap_[_id] = new ConditionInfo<float>(_value, StateMachine_C::ParameterType::FLOAT);
}

void StateMachine::AddIntConditionInfo(ConditionID _id, int _value)
{
	conditionMap_[_id] = new ConditionInfo<int>(_value, StateMachine_C::ParameterType::INT);
}

void StateMachine::RemoveCondition(ConditionID _id)
{
	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return;

	const IConditionInfo* conditionInfoToRemove = it->second;


	for (auto& t : transitions_)
	{
		if (!t.condition_)
			continue;

		AndCondition* andCond = t.condition_;

		if (!andCond)
			continue;

		IFsmCondition* conditionToRemove = andCond->FindByConditionInfo(conditionInfoToRemove);

		if (!conditionToRemove)
			continue;

		andCond->Remove(conditionToRemove);

	}

	conditionMap_.erase(it);
}

void StateMachine::SetBoolConditionInfo(ConditionID _id, bool _value)
{
	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return;

	auto condInfo = dynamic_cast<ConditionInfo<bool>*>(it->second);

	if (condInfo)
		condInfo->value = _value;
}

void StateMachine::SetFloatConditionInfo(ConditionID _id, float _value)
{

	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return;

	auto condInfo = dynamic_cast<ConditionInfo<float>*>(it->second);

	if (condInfo)
		condInfo->value = _value;
}

void StateMachine::SetIntConditionInfo(ConditionID _id, int _value)
{
	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return;

	auto condInfo = dynamic_cast<ConditionInfo<int>*>(it->second);

	if (condInfo)
		condInfo->value = _value;
}

void StateMachine::SetBoolCondition(const ConditionID _id, const StateID _from, const StateID _to, const bool _expected)
{
	SetBoolConditionNoSafeCheck(_id, _from, _to, _expected);
}

void StateMachine::SetFloatCondition(const ConditionID _id, StateID _from, StateID _to, const float _compareTo, const StateMachine_C::Comparator& _comp)
{
	SetFloatConditionNoSafeCheck(_id, _from, _to, _compareTo, _comp);
}

void StateMachine::SetIntCondition(const ConditionID _id, IStateMachine::StateID _from, IStateMachine::StateID _to, const int _compareTo, const StateMachine_C::Comparator& _comp)
{
	SetIntConditionNoSafeCheck(_id, _from, _to, _compareTo, _comp);
}

void StateMachine::SetBoolConditionForAnyTransition(ConditionID _id, StateID _to, bool _expected)
{
	SetBoolConditionNoSafeCheck(_id, ANY_STATE_ID, _to, _expected);
}

void StateMachine::SetBoolConditionForExitTransition(ConditionID _id, StateID _from, bool _expected)
{
	SetBoolConditionNoSafeCheck(_id, _from, EXIT_STATE_ID, _expected);
}

void StateMachine::SetFloatConditionForAnyTransition(ConditionID _id, StateID _to, float _compareTo,
	const StateMachine_C::Comparator& _comp)
{
	SetFloatConditionNoSafeCheck(_id, ANY_STATE_ID, _to, _compareTo, _comp);
}

void StateMachine::SetFloatConditionForExitTransition(ConditionID _id, StateID _from, float _compareTo,
	const StateMachine_C::Comparator& _comp)
{
	SetFloatCondition(_id, _from, EXIT_STATE_ID, _compareTo, _comp);
}

void StateMachine::SetIntConditionForAnyTransition(ConditionID _id, StateID _to, int _compareTo,
	const StateMachine_C::Comparator& _comp)
{
	SetIntCondition(_id, ANY_STATE_ID, _to, _compareTo, _comp);
}

void StateMachine::SetIntConditionForExitTransition(ConditionID _id, StateID _from, int _compareTo,
	const StateMachine_C::Comparator& _comp)
{
	SetIntCondition(_id, _from, EXIT_STATE_ID, _compareTo, _comp);
}

const IConditionInfo* StateMachine::GetConditionInfo(ConditionID _conditionID) const
{
	auto it = conditionMap_.find(_conditionID);

	if (it == conditionMap_.end())
		return nullptr;

	return it->second;
}

const IFsmCondition* StateMachine::GetCondition(const ConditionID _id, const StateID _from, const StateID _to) const
{
	auto it = conditionMap_.find(_id);

	if (it == conditionMap_.end())
		return nullptr;

	const IConditionInfo* condInfo = it->second;

	for (auto& t : transitions_)
	{
		if (!t.condition_)
			continue;

		if (!(t.from_ == _from && t.to_ == _to))
			continue;

		AndCondition* andCond = t.condition_;

		return andCond->FindByConditionInfo(condInfo);
	}

	return nullptr;
}

void StateMachine::ReceiveInput(void(*InputHandle)(IStateMachine&))
{
	if (!InputHandle)
		return;

	InputHandle(*this);
}

bool StateMachine::IsStateMachineExited() const
{
	return currentState_ == nullptr;
}

void StateMachine::ResetStateMachine()
{
	for (auto it = stateMap_.begin(); it != stateMap_.end(); ++it)
	{
		if (!it->second)
			continue;

		if (!it->second->AsStateMachine())
			continue;

		IStateMachine* innerMachine = dynamic_cast<IStateMachine*>(it->second);
		if (innerMachine)
			innerMachine->ResetStateMachine();
	}

	stateMap_.clear();

	transitions_.clear();

	for (auto it = conditionMap_.begin(); it != conditionMap_.end(); ++it)
	{
		if (it->second)
		{
			delete it->second;
			it->second = nullptr;
		}
	}

	conditionMap_.clear();

	currentState_ = nullptr;

	currentStateID_ = NONE;

	initialState_ = nullptr;

	initialStateID_ = NONE;
}

bool StateMachine::IsEmpty() const
{
	if (!stateMap_.empty())
		return false;

	if (!transitions_.empty())
		return false;

	if (!conditionMap_.empty())
		return false;

	if (currentState_)
			

		if (currentStateID_!=NULL)
			return false;

	if (initialState_)
		return false;

	if (initialStateID_ != NULL)
		return false;

	return true;
}

StateMachine::StateID StateMachine::GetExitStateID() const
{
	return EXIT_STATE_ID;
}

StateMachine::StateID StateMachine::GetAnyStateID() const
{
	return ANY_STATE_ID;
}

StateMachine::StateID StateMachine::GetNoneStateID() const
{
	return NONE;
}
