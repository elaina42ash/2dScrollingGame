#include "Component/Common/DecisionLogicalComponent/Class/StateComponent.h"
#include "StateMachine/StateMachine.h"

StateComponent::StateComponent(bool _isActive, IMessenger* _messenger) : DecisionLogicalComponent(_isActive, _messenger)
{
	InitializeDefaults();
}

StateComponent::StateComponent(IMessenger* _messenger) : DecisionLogicalComponent(_messenger)
{
	InitializeDefaults();
}

void StateComponent::Init()
{
	DecisionLogicalComponent::Init();
}

void StateComponent::Render()
{
	DecisionLogicalComponent::Render();
}

void StateComponent::Term()
{
	DecisionLogicalComponent::Term();
}

void StateComponent::Update()
{
	DecisionLogicalComponent::Update();
}

bool StateComponent::IsSemanticInputTriggered(GameSemantic::Semantic _semantic) const
{
	return semanticInputBuffer_.IsSemanticInputTriggered(_semantic);
}

void StateComponent::InitializeDefaults()
{
	stateMachine_ = new StateMachine();
}

int StateComponent::GetCurrentStateID(IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return -1;

	return stateMachine_->CurrentStateId();
}

void StateComponent::AddState(StateID _stateID, IState* _state, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	auto it = stateTable_.find(_stateID);
	if (it != stateTable_.end())
		return;
	stateTable_.insert({ _stateID ,_state });
	_stateMachine->AddState(_stateID, _state);
}

void StateComponent::RemoveState(StateID _stateID, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	auto it = stateTable_.find(_stateID);
	if (it == stateTable_.end())
		return;
	_stateMachine->RemoveState(_stateID);
	stateTable_.erase(it);
}

void StateComponent::AddBoolConditionInfo(ConditionID _conditionID, const char* _name, const bool _value, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	auto it = conditionTable_.find(_conditionID);

	if (it != conditionTable_.end())
		return;

	conditionTable_.insert({ _conditionID ,_name });

	_stateMachine->AddBoolConditionInfo(_conditionID, _value);
}

void StateComponent::AddIntConditionInfo(ConditionID _conditionID, const char* _name, const int _value, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	auto it = conditionTable_.find(_conditionID);

	if (it != conditionTable_.end())
		return;

	conditionTable_.insert({ _conditionID ,_name });

	_stateMachine->AddIntConditionInfo(_conditionID, _value);
}

void StateComponent::AddFloatConditionInfo(ConditionID _conditionID, const char* _name, const float _value, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	auto it = conditionTable_.find(_conditionID);

	if (it != conditionTable_.end())
		return;

	conditionTable_.insert({ _conditionID ,_name });

	_stateMachine->AddFloatConditionInfo(_conditionID, _value);
}

void StateComponent::SetBoolConditionInfo(ConditionID _conditionID, const bool _value, IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return;

	_stateMachine->SetBoolConditionInfo(_conditionID, _value);
}

void StateComponent::SetBoolConditionForAnyTransition(ConditionID _id, StateID _to, bool _expected, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;
	_stateMachine->SetBoolConditionForAnyTransition(_id, _to, _expected);
}

void StateComponent::SetBoolConditionForExitTransition(ConditionID _id, StateID _from, bool _expected, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;
	_stateMachine->SetBoolConditionForExitTransition(_id, _from, _expected);
}

void StateComponent::SetIntConditionForAnyTransition(ConditionID _id, StateID _to, int _compareTo,
	const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;
	_stateMachine->SetIntConditionForAnyTransition(_id, _to, _compareTo, _comp);
}

void StateComponent::SetIntConditionForExitTransition(ConditionID _id, StateID _from, int _compareTo,
	const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;
	_stateMachine->SetIntConditionForExitTransition(_id, _from, _compareTo, _comp);
}

void StateComponent::SetFloatConditionForAnyTransition(ConditionID _id, StateID _to, float _compareTo,
	const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;
	_stateMachine->SetFloatConditionForAnyTransition(_id, _to, _compareTo, _comp);
}

void StateComponent::SetFloatConditionForExitTransition(ConditionID _id, StateID _from, float _compareTo,
	const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;
	_stateMachine->SetFloatConditionForExitTransition(_id, _from, _compareTo, _comp);
}

void StateComponent::SetIntConditionInfo(const ConditionID _conditionID, const int _value, IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return;

	_stateMachine->SetIntConditionInfo(_conditionID, _value);
}

void StateComponent::SetFloatConditionInfo(const ConditionID _conditionID, const float _value, IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return;

	_stateMachine->SetFloatConditionInfo(_conditionID, _value);
}

void StateComponent::SetBoolCondition(ConditionID _id, const TransitionKey& _transitionID, bool _expected, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->SetBoolCondition(_id, _transitionID.from, _transitionID.to, _expected);
}

void StateComponent::SetFloatCondition(ConditionID _id, const TransitionKey& _transitionID, float _compareTo, const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->SetFloatCondition(_id, _transitionID.from, _transitionID.to, _compareTo, _comp);
}

void StateComponent::SetIntCondition(ConditionID _id, const TransitionKey& _transitionID, int _compareTo, const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->SetIntCondition(_id, _transitionID.from, _transitionID.to, _compareTo, _comp);
}

const IConditionInfo* const StateComponent::GetConditionInfo(const ConditionID _conditionID, const IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return nullptr;

	const IConditionInfo* const conditionInfo = _stateMachine->GetConditionInfo(_conditionID);

	return  conditionInfo;
}

const IFsmCondition* const StateComponent::GetCondition(const ConditionID _conditionID, const TransitionKey& _transitionID, const IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return nullptr;

	const IFsmCondition* const condition = _stateMachine->GetCondition(_conditionID, _transitionID.from, _transitionID.to);

	return  condition;
}

void StateComponent::AddConditionToTransition(const ConditionID _condition, const TransitionKey& _transitionID, IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return;

	_stateMachine->AddConditionToTransition(_condition, _transitionID.from, _transitionID.to);
}

void StateComponent::AddConditionToAnyTransition(ConditionID _conditionID, StateID _to, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->AddConditionToAnyTransition(_conditionID, _to);
}

void StateComponent::AddConditionToExitTransition(ConditionID _conditionID, StateID _from, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->AddConditionToExitTransition(_conditionID, _from);
}

void StateComponent::RemoveCondition(const ConditionID _conditionID, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->RemoveCondition(_conditionID);
	conditionTable_.erase(_conditionID);
}

void StateComponent::RemoveConditionFromTransition(const ConditionID _conditionID, const TransitionKey& _transitionID, IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return;

	_stateMachine->RemoveConditionFromTransition(_conditionID, _transitionID.from, _transitionID.to);
}

void StateComponent::AddTransition(const TransitionKey& _transitionID, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	auto it = std::find_if(transitions_.begin(), transitions_.end(), [_transitionID](const TransitionKey& t)
		{
			return _transitionID.from == t.from && _transitionID.to == t.to;
		});

	if (it != transitions_.end())
		return;

	transitions_.push_back(_transitionID);

	_stateMachine->AddTransition(_transitionID.from, _transitionID.to);
}

void StateComponent::AddTransitionToExit(StateID _from, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->AddTransitionToExit(_from);
}

void StateComponent::AddTransitionFromAny(StateID _to, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->AddTransitionFromAny(_to);
}

void StateComponent::RemoveTransition(const TransitionKey& _transitionID, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	auto it = std::find_if(transitions_.begin(), transitions_.end(), [_transitionID](const TransitionKey& t)
		{
			return _transitionID.from == t.from && _transitionID.to == t.to;
		});

	if (it == transitions_.end())
		return;

	transitions_.erase(std::remove_if(transitions_.begin(), transitions_.end(), [_transitionID](const TransitionKey& t)
		{
			return _transitionID.from == t.from && _transitionID.to == t.to;
		}), transitions_.end()
			);

	_stateMachine->RemoveTransition(_transitionID.from, _transitionID.to);
}

void StateComponent::ResetStateMachine(IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;
	if (_stateMachine == stateMachine_)
	{
		conditionTable_.clear();

		transitions_.clear();

		std::unordered_map<StateID, IState*> stateTable_;

		for (auto it = stateTable_.begin(); it != stateTable_.end(); ++it)
		{
			if (!it->second)
				continue;

			if (!it->second->AsStateMachine())
				continue;

			IStateMachine* stateMachine = dynamic_cast<IStateMachine*>(it->second);

			if (!stateMachine)
				continue;

			stateMachine->ResetStateMachine();
;		}

		for (auto it = stateTable_.begin(); it != stateTable_.end(); ++it)
		{
			if (it->second)
			{
				delete it->second;
				it->second = nullptr;
			}
		}
		stateTable_.clear();

		IStateMachine* stateMachine_ = nullptr;
	}
	else
	{
		_stateMachine->ResetStateMachine();
	}
}

IStateComponent::StateID StateComponent::GetAnyStateID(IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return GetNoneStateID(_stateMachine);

	return _stateMachine->GetAnyStateID();
}

IStateComponent::StateID StateComponent::GetExitStateID(IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return GetNoneStateID(_stateMachine);

	return _stateMachine->GetExitStateID();
}

IStateComponent::StateID StateComponent::GetNoneStateID(IStateMachine* _stateMachine) const
{
	if (!_stateMachine)
		return INT_MIN;
	return _stateMachine->GetNoneStateID();
}

void StateComponent::Reset()
{
	DecisionLogicalComponent::Reset();

	semanticInputBuffer_.ClearAllSemanticInputs();
}

void StateComponent::MarkSemanticInput(const GameSemantic::Semantic _semantic)
{
	semanticInputBuffer_.MarkSemanticInput(_semantic);
}

void StateComponent::SetInitialState(const StateID _stateID, IStateMachine* _stateMachine)
{
	if (!_stateMachine)
		return;

	_stateMachine->SetInitialState(_stateID);
}

