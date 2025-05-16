#pragma once
#include <unordered_map>
#include "IStateMachine.h"
#include "Condition/AndCondition.h"
#include "Condition/ConditionInfo.h"
#include "State/IState.h"
#include "Transition/Transition.h"

class StateMachine :public IStateMachine
{
private:
	using StateID = int;

	constexpr static  StateID MIN_USER_STATE_ID = -10000;

	constexpr static StateID NONE = MIN_USER_STATE_ID - 1;
	constexpr static StateID EXIT_STATE_ID = NONE - 1;
	constexpr static StateID ANY_STATE_ID = NONE - 2;

private:
	std::unordered_map<StateID, IState*> stateMap_;

	std::vector<Transition> transitions_;

	std::unordered_map<ConditionID, IConditionInfo*> conditionMap_;

	IState* currentState_ = nullptr;

	StateID currentStateID_ = NONE;

	IState* initialState_ = nullptr;

	StateID initialStateID_ = NONE;

	void ChangeState(StateID _id);

	void ChangeStateToExit();

	void RemoveTransitionAssociatedWith(StateID _id);

	void ValidateUserStateID(StateID _id) const;

	void AddTransitionNoSafeCheck(StateID _from, StateID _to);

	void AddConditionToTransitionNoSafeCheck(ConditionID _id, StateID _from, StateID _to);

	void SetBoolConditionNoSafeCheck(ConditionID _id, IStateMachine::StateID _from, IStateMachine::StateID _to, bool _expected);

	void SetFloatConditionNoSafeCheck(ConditionID _id, IStateMachine::StateID _from, IStateMachine::StateID _to, float _compareTo, const StateMachine_C::Comparator& _comp);

	void SetIntConditionNoSafeCheck(ConditionID _id, IStateMachine::StateID _from, IStateMachine::StateID _to, int _compareTo, const StateMachine_C::Comparator& _comp);

public:
	StateMachine();

	~StateMachine() override;

	void AddState(StateID _id, IState* _state) override;

	void RemoveState(StateID _id) override;

	void AddTransition(StateID _from, StateID _to) override;

	void RemoveTransition(StateID _from, StateID _to) override;

	void AddTransitionToExit(StateID _from) override;

	void AddTransitionFromAny(StateID _to) override;

	void SetInitialState(StateID _id) override;


	bool TryExecuteTransitionFrom(int _from);

	void Update() override;

	int CurrentStateId() const override;

	void AddConditionToTransition(ConditionID _id, StateID _from, StateID _to) override;

	void AddConditionToAnyTransition(ConditionID _conditionID, StateID _to) override;

	void AddConditionToExitTransition(ConditionID _conditionID, StateID _from) override;

	void RemoveConditionFromTransition(ConditionID _id, StateID _from, StateID _to) override;

	void AddActionToTransition(const std::function<void()>& _action, StateID _from, StateID _to) override;

	void RemoveActionFromTransition(StateID _from, StateID _to) override;

	void AddBoolConditionInfo(ConditionID _id, bool _value) override;

	void AddFloatConditionInfo(ConditionID _id, float _value) override;

	void AddIntConditionInfo(ConditionID _id, int _value) override;

	void RemoveCondition(ConditionID _id) override;

	void SetBoolConditionInfo(ConditionID _id, bool _value) override;

	void SetFloatConditionInfo(ConditionID _id, float _value) override;

	void SetIntConditionInfo(ConditionID _id, int _value) override;

	void SetBoolCondition(ConditionID _id, IStateMachine::StateID _from, IStateMachine::StateID _to, bool _expected) override;

	void SetFloatCondition(ConditionID _id, IStateMachine::StateID _from, IStateMachine::StateID _to, float _compareTo, const StateMachine_C::Comparator& _comp) override;

	void SetIntCondition(ConditionID _id, IStateMachine::StateID _from, IStateMachine::StateID _to, int _compareTo, const StateMachine_C::Comparator& _comp) override;

	void SetBoolConditionForAnyTransition(ConditionID _id, StateID _to, bool _expected) override;

	void SetBoolConditionForExitTransition(ConditionID _id, StateID _from, bool _expected) override;

	void SetFloatConditionForAnyTransition(ConditionID _id, StateID _to, float _compareTo,
		const StateMachine_C::Comparator& _comp) override;

	void SetFloatConditionForExitTransition(ConditionID _id, StateID _from, float _compareTo,
		const StateMachine_C::Comparator& _comp) override;

	void SetIntConditionForAnyTransition(ConditionID _id, StateID _to, int _compareTo,
		const StateMachine_C::Comparator& _comp) override;

	void SetIntConditionForExitTransition(ConditionID _id, StateID _from, int _compareTo,
		const StateMachine_C::Comparator& _comp) override;

	const IConditionInfo* GetConditionInfo(ConditionID _conditionID) const override;

	const IFsmCondition* GetCondition(ConditionID _id, StateID _from, StateID _to) const override;

	void ReceiveInput(void(*InputHandle)(IStateMachine&)) override;

	bool IsStateMachineExited() const override;

	void ResetStateMachine() override;

	bool IsEmpty() const override;

	StateID GetExitStateID() const override;

	StateID GetAnyStateID() const override;

	StateID GetNoneStateID() const override;
};

