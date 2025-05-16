#pragma once
#include "IStateMachine.h"
#include "StateMachine.h"
#include "State/State.h"


class InnerStateMachine : public State, public IStateMachine
{
private:
	IStateMachine* innerFsm_;

public:
	InnerStateMachine(IStateMachine* _parent, IMessenger* _messenger);

	~InnerStateMachine() override;

	void Enter() override;

	void Update() override;

	void Exit() override;

	void AddState(StateID _id, IState* _state) override final;

	void RemoveState(StateID _id) override final;

	int CurrentStateId() const override final;

	void AddTransition(StateID _from, StateID _to) override final;

	void RemoveTransition(StateID _from, StateID _to) override final;

	void AddTransitionFromAny(StateID _to) override final;

	void AddConditionToTransition(ConditionID _id, StateID _from, StateID _to) override final;

	void AddConditionToAnyTransition(ConditionID _conditionID, StateID _to) override final;

	void AddConditionToExitTransition(ConditionID _conditionID, StateID _from) override final;

	void RemoveConditionFromTransition(ConditionID _id, StateID _from, StateID _to) override final;

	void AddActionToTransition(const std::function<void()>& _action, StateID _from, StateID _to) override final;

	void RemoveActionFromTransition(StateID _from, StateID _to) override final;

	void SetInitialState(StateID _id) override final;

	void AddBoolConditionInfo(ConditionID _id, bool _value) override final;

	void AddFloatConditionInfo(ConditionID _id, float _value) override final;

	void AddIntConditionInfo(ConditionID _id, int _value) override final;

	void RemoveCondition(ConditionID _id) override final;

	void SetBoolConditionInfo(ConditionID _id, bool _value) override final;

	void SetFloatConditionInfo(ConditionID _id, float _value) override final;

	void SetIntConditionInfo(ConditionID _id, int _value) override final;

	void SetBoolCondition(ConditionID _id, StateID _from, StateID _to, bool _expected) override final;

	void SetFloatCondition(ConditionID _id, StateID _from, StateID _to, float _compareTo, const StateMachine_C::Comparator& _comp) override final;

	void SetIntCondition(ConditionID _id, StateID _from, StateID _to, int _compareTo, const StateMachine_C::Comparator& _comp) override final;

	void SetBoolConditionForAnyTransition(ConditionID _id, StateID _to, bool _expected) override final;

	void SetBoolConditionForExitTransition(ConditionID _id, StateID _from, bool _expected) override final;

	void SetFloatConditionForAnyTransition(ConditionID _id, StateID _to, float _compareTo,
	                                       const StateMachine_C::Comparator& _comp) override final;

	void SetFloatConditionForExitTransition(ConditionID _id, StateID _from, float _compareTo,
	                                        const StateMachine_C::Comparator& _comp) override final;

	void SetIntConditionForAnyTransition(ConditionID _id, StateID _to, int _compareTo,
	                                     const StateMachine_C::Comparator& _comp) override final;

	void SetIntConditionForExitTransition(ConditionID _id, StateID _from, int _compareTo,
	                                      const StateMachine_C::Comparator& _comp) override final;

	const IConditionInfo* GetConditionInfo(ConditionID _conditionID) const override final;

	const IFsmCondition* GetCondition(ConditionID _conditionID, StateID _from, StateID _to) const override final;

	void ReceiveInput(void(*_inputHandle)(IStateMachine&)) override final;

	void AddTransitionToExit(StateID _from) override final;

	bool IsStateMachineExited() const override final;

	IStateMachine* AsStateMachine() override;

	void ResetStateMachine() override;

	bool IsEmpty() const override;

	StateID GetExitStateID() const override;

	StateID GetAnyStateID() const override;

	StateID GetNoneStateID() const override;
};
