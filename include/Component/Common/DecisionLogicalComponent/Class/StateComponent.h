#pragma once
#include "DecisionLogicalComponent.h"
#include "Component/Common/DecisionLogicalComponent/Interface/IStateComponent.h"
#include "Semantic/SemanticInputBuffer.h"
#include "StateMachine/InnerStateMachine.h"
#include "StateMachine/IStateMachine.h"
#include "StateMachine/State/IState.h"

#pragma warning(push)
#pragma warning(disable:4250)
class StateComponent : public DecisionLogicalComponent, public IStateComponent
{
protected:
	using ConditionID = int;

	struct TransitionKey
	{
		StateID from;
		StateID to;
		bool operator==(const TransitionKey& _other) const
		{
			return  from == _other.from && to == _other.to;
		}
	};

	bool isStageCleared = false;

private:
	std::unordered_map<ConditionID, const char*> conditionTable_;

	std::vector<TransitionKey> transitions_;

	SemanticInputBuffer semanticInputBuffer_;

protected:
	std::unordered_map<StateID, IState*> stateTable_;

	IStateMachine* stateMachine_;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	bool IsSemanticInputTriggered(GameSemantic::Semantic _semantic) const override final;

	int GetCurrentStateID(IStateMachine* _stateMachine) const override final;

protected:
	StateComponent(bool _isActive, IMessenger* _messenger);

	explicit StateComponent(IMessenger* _messenger);

	void Reset() override;

	void MarkSemanticInput(GameSemantic::Semantic _semantic);

#pragma region Statemachine Function
	void SetInitialState(StateID _stateID, IStateMachine* _stateMachine);

	void AddState(StateID _stateID, IState* _state, IStateMachine* _stateMachine);

	void RemoveState(StateID _stateID, IStateMachine* _stateMachine);

	void AddBoolConditionInfo(ConditionID _conditionID, const char* _name, bool _value, IStateMachine* _stateMachine);

	void AddIntConditionInfo(ConditionID _conditionID, const char* _name, int _value, IStateMachine* _stateMachine);

	void AddFloatConditionInfo(ConditionID _conditionID, const char* _name, float _value, IStateMachine* _stateMachine);

	void SetBoolConditionInfo(ConditionID _conditionID, bool _value, IStateMachine* _stateMachine) const;

	void SetBoolConditionForAnyTransition(ConditionID _id, StateID _to, bool _expected, IStateMachine* _stateMachine);

	void SetBoolConditionForExitTransition(ConditionID _id, StateID _from, bool _expected, IStateMachine* _stateMachine);

	void SetIntConditionInfo(ConditionID _conditionID, int _value, IStateMachine* _stateMachine) const;

	void SetIntConditionForAnyTransition(ConditionID _id, StateID _to, int _compareTo, const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine);

	void SetIntConditionForExitTransition(ConditionID _id, StateID _from, int _compareTo, const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine);

	void SetFloatConditionInfo(ConditionID _conditionID, float _value, IStateMachine* _stateMachine) const;

	void SetFloatConditionForAnyTransition(ConditionID _id, StateID _to, float _compareTo, const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine);

	void SetFloatConditionForExitTransition(ConditionID _id, StateID _from, float _compareTo, const StateMachine_C::Comparator& _comp, IStateMachine* _stateMachine);

	void SetBoolCondition(ConditionID _id, const TransitionKey& _transitionID, bool _expected, IStateMachine* _stateMachine);

	void SetFloatCondition(ConditionID _id, const TransitionKey& _transitionID, float _compareTo, const StateMachine_C::Comparator& _comp, IStateMachine
		* _stateMachine);

	void SetIntCondition(ConditionID _id, const TransitionKey& _transitionID, int _compareTo, const StateMachine_C::Comparator& _comp, IStateMachine
		* _stateMachine);

	const IConditionInfo* const GetConditionInfo(ConditionID _conditionID, const IStateMachine* _stateMachine) const;

	const IFsmCondition* const GetCondition(ConditionID _conditionID, const TransitionKey& _transitionID, const IStateMachine* _stateMachine) const;

	void AddConditionToTransition(ConditionID _condition, const TransitionKey& _transitionID, IStateMachine* _stateMachine) const;

	void AddConditionToAnyTransition(ConditionID _conditionID, StateID _to, IStateMachine* _stateMachine);

	void AddConditionToExitTransition(ConditionID _conditionID, StateID _from, IStateMachine* _stateMachine);

	void RemoveCondition(ConditionID _conditionID, IStateMachine* _stateMachine);

	void RemoveConditionFromTransition(ConditionID _conditionID, const TransitionKey& _transitionID, IStateMachine* _stateMachine) const;

	void AddTransition(const TransitionKey& _transitionID, IStateMachine* _stateMachine);

	void AddTransitionToExit(StateID _from, IStateMachine* _stateMachine);

	void AddTransitionFromAny(StateID _to, IStateMachine* _stateMachine);

	void RemoveTransition(const TransitionKey& _transitionID, IStateMachine* _stateMachine);

	void ResetStateMachine(IStateMachine* _stateMachine);

	StateID GetAnyStateID(IStateMachine* _stateMachine) const;

	StateID GetExitStateID(IStateMachine* _stateMachine) const;

	StateID GetNoneStateID(IStateMachine* _stateMachine) const;
#pragma endregion

private:

	void InitializeDefaults();

};
#pragma warning(pop)