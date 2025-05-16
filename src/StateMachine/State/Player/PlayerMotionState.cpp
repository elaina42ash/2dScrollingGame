#include "StateMachine/State/Player/PlayerMotionState.h"

#include "Fwk/Framework.h"
#include "StateMachine/State/Player/PlayerStateDef.h"

PlayerMotionState::PlayerMotionState(IStateMachine* _parent, IMessenger* _messenger) : InnerStateMachine(_parent, _messenger)
{
}

void PlayerMotionState::Enter()
{
	InnerStateMachine::Enter();
	DebugLog("[enter stateMachine] player Motion");
}

void PlayerMotionState::Update()
{
	InnerStateMachine::Update();
}

void PlayerMotionState::Exit()
{
	InnerStateMachine::Exit();

	bool isDead = false;
	bool isClear = false;

	const IConditionInfo* deadConditionInfo = GetConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DEAD));
	const IConditionInfo* clearConditionInfo = GetConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_CLEAR));

	if (deadConditionInfo&& deadConditionInfo->GetType()==StateMachine_C::ParameterType::BOOL)
	{
		isDead = deadConditionInfo->GetBoolValue();
	}

	if (clearConditionInfo&& clearConditionInfo->GetType()==StateMachine_C::ParameterType::BOOL)
	{
		isClear = clearConditionInfo->GetBoolValue();
	}

	if (IsStateMachineExited())
	{
		if (isDead)
		{
			parent_->SetBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::IS_DEAD), true);
		}

		if (isClear)
		{
			parent_->SetBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::IS_CLEAR), true);
		}
	}

	DebugLog("[exit stateMachine] player Motion");
}

IStateMachine* PlayerMotionState::AsStateMachine()
{
	return this;
}
