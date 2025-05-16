#pragma once
#include <functional>
#include "StateMachineDef.h"
#include "Condition/IConditionInfo.h"
#include "Condition/IFsmCondition.h"


class IState;
class IStateMachine
{
public:
	using StateID = int;
	using ConditionID = int;

public:
	virtual  ~IStateMachine() = default;

	virtual void AddState(StateID _id, IState* _state) = 0;
	virtual void RemoveState(StateID _id) = 0;

	virtual int CurrentStateId() const = 0;

	virtual void AddTransition(StateID _from, StateID _to) = 0;
	virtual void AddTransitionToExit(StateID _from) = 0;
	virtual void AddTransitionFromAny(StateID _to) = 0;

	virtual void RemoveTransition(StateID _from, StateID _to) = 0;

	virtual void AddConditionToTransition(ConditionID _id, StateID _from, StateID _to) = 0;
	virtual void AddConditionToAnyTransition(ConditionID _conditionID, StateID _to) =0;
	virtual void AddConditionToExitTransition(ConditionID _conditionID, StateID _from) =0;

	virtual void RemoveConditionFromTransition(ConditionID _id, StateID _from, StateID _to) = 0;

	virtual void AddActionToTransition(const std::function<void()>& _action, StateID _from, StateID _to) = 0;
	virtual void RemoveActionFromTransition(StateID _from, StateID _to) = 0;

	virtual void SetInitialState(StateID _id) = 0;

	virtual void Update() = 0;

	virtual void AddBoolConditionInfo(ConditionID _id, bool _value) = 0;
	virtual void AddFloatConditionInfo(ConditionID _id, float _value) = 0;
	virtual void AddIntConditionInfo(ConditionID _id, int _value) = 0;

	virtual void RemoveCondition(ConditionID _id) = 0;

	virtual void SetBoolConditionInfo(ConditionID _id, bool _value) = 0;
	virtual void SetFloatConditionInfo(ConditionID _id, float _value) = 0;
	virtual void SetIntConditionInfo(ConditionID _id, int _value) = 0;

	virtual void SetBoolCondition(ConditionID _id, StateID _from, StateID _to, bool _expected) = 0;
	virtual void SetBoolConditionForAnyTransition(ConditionID _id, StateID _to, bool _expected) =0;
	virtual void SetBoolConditionForExitTransition(ConditionID _id, StateID _from, bool _expected) =0;
	virtual void SetFloatCondition(ConditionID _id, StateID _from, StateID _to, float _compareTo, const StateMachine_C::Comparator& _comp) = 0;
	virtual void SetFloatConditionForAnyTransition(ConditionID _id, StateID _to, float _compareTo, const StateMachine_C::Comparator& _comp) = 0;
	virtual void SetFloatConditionForExitTransition(ConditionID _id, StateID _from, float _compareTo, const StateMachine_C::Comparator& _comp) = 0;
	virtual void SetIntCondition(ConditionID _id, StateID _from, StateID _to, int _compareTo, const StateMachine_C::Comparator& _comp) = 0;
	virtual void SetIntConditionForAnyTransition(ConditionID _id, StateID _to, int _compareTo, const StateMachine_C::Comparator& _comp) = 0;
	virtual void SetIntConditionForExitTransition(ConditionID _id, StateID _from, int _compareTo, const StateMachine_C::Comparator& _comp) = 0;

	virtual const IConditionInfo* GetConditionInfo(ConditionID _conditionID) const = 0;
	virtual const IFsmCondition* GetCondition(ConditionID _conditionID, StateID _from, StateID _to) const = 0;

	virtual void ReceiveInput(void (*_inputHandle)(IStateMachine&)) = 0; // 外部输入接口

	virtual bool IsStateMachineExited() const = 0;

	virtual void ResetStateMachine() = 0;

	virtual bool IsEmpty() const = 0;

	virtual StateID GetExitStateID() const = 0;

	virtual StateID GetAnyStateID() const = 0;

	virtual StateID GetNoneStateID() const = 0;
};
