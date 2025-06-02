#include "Component/Player/DecisionLogicalComponent/Class/PlayerStateComponent.h"
#include "Component/Common/DecisionLogicalComponent/Class/StateComponent.h"
#include "Event/Message/LogicalInputMsg/AttackInputMsg.h"
#include "Event/Message/LogicalInputMsg/DashInputMsg.h"
#include "Event/Message/LogicalInputMsg/HoriAxisInputMsg.h"
#include "Event/Message/LogicalInputMsg/InteractInputMsg.h"
#include "Event/Message/LogicalInputMsg/JumpInputMsg.h"
#include "Event/Message/LogicalInputMsg/ReleaseJumpInputMsg.h"
#include "Event/Message/LogicalInputMsg/SwitchWeaponInputMsg.h"
#include "Event/Message/SemanticMsg/StartStageClearSemMsg.h"
#include "Event/Message/StateMsg/SetIsClearConditionMsg.h"
#include "Event/Message/StateMsg/SetIsDamagedConditionMsg.h"
#include "Event/Message/StateMsg/SetIsDeadConditionMsg.h"
#include "StateMachine/InnerStateMachine.h"
#include "StateMachine/State/Player/PlayerAirState.h"
#include "StateMachine/State/Player/PlayerAttackState.h"
#include "StateMachine/State/Player/PlayerDamagedState.h"
#include "StateMachine/State/Player/PlayerDashState.h"
#include "StateMachine/State/Player/PlayerDeadState.h"
#include "StateMachine/State/Player/PlayerIdleState.h"
#include "StateMachine/State/Player/PlayerMotionState.h"
#include "StateMachine/State/Player/PlayerMovingState.h"
#include "StateMachine/State/Player/PlayerStageClearState.h"
#include "StateMachine/State/Player/PlayerStateDef.h"


PlayerStateComponent::PlayerStateComponent(bool _isActive, IMessenger* _messenger, IPlayerView* _playerView) : StateComponent(_isActive, _messenger),
playerView_(_playerView)
{
}

PlayerStateComponent::PlayerStateComponent(IMessenger* _messenger, IPlayerView* _playerView) : StateComponent(_messenger),
playerView_(_playerView)
{
}

void PlayerStateComponent::InitializeMotionStateMachine(InnerStateMachine* motionStateMachine)
{
	AddBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_MOVING), "isMoving", false, motionStateMachine);
	AddBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_AIR), "isAir", false, motionStateMachine);
	AddBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DAMAGED), "isDamaged", false, motionStateMachine);
	AddBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), "isAttacking", false, motionStateMachine);
	AddBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DEAD), "isDead", false, motionStateMachine);
	AddBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), "isDashing", false, motionStateMachine);
	AddBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_CLEAR), "isClear", false, motionStateMachine);

	PlayerMovingState* movingState = new PlayerMovingState(motionStateMachine, GetMessengerPtr(), this, this, playerView_.Injected());
	PlayerIdleState* idleState = new PlayerIdleState(motionStateMachine, GetMessengerPtr(), this, this, playerView_.Injected());
	PlayerAirState* airState = new PlayerAirState(motionStateMachine, GetMessengerPtr(), this, this, playerView_.Injected());
	PlayerDamagedState* damagedState = new PlayerDamagedState(motionStateMachine, GetMessengerPtr(), this, this, playerView_.Injected());
	PlayerAttackState* attackState = new PlayerAttackState(motionStateMachine, GetMessengerPtr(), this, this, playerView_.Injected());
	PlayerDashState* dashState = new PlayerDashState(motionStateMachine, GetMessengerPtr(), this, this, playerView_.Injected());

	AddState(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_MOVING), movingState, motionStateMachine);
	AddState(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE), idleState, motionStateMachine);
	AddState(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_AIR), airState, motionStateMachine);
	AddState(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DAMAGED), damagedState, motionStateMachine);
	AddState(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_ATTACK), attackState, motionStateMachine);
	AddState(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DASH), dashState, motionStateMachine);

	SetInitialState(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE), motionStateMachine);

	TransitionKey idle_to_moving = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_MOVING) };
	TransitionKey idle_to_air = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_AIR) };
	TransitionKey idle_to_attack = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_ATTACK) };
	TransitionKey idle_to_dash = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DASH) };
	TransitionKey moving_to_idle = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_MOVING),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE) };
	TransitionKey moving_to_air = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_MOVING),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_AIR) };
	TransitionKey moving_to_dash = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_MOVING),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DASH) };
	TransitionKey air_to_idle = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_AIR),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE) };
	TransitionKey air_to_attack = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_AIR),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_ATTACK) };
	TransitionKey air_to_dash = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_AIR),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DASH) };
	TransitionKey damaged_to_idle = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DAMAGED),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE) };
	TransitionKey moving_to_attack = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_MOVING),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_ATTACK) };
	TransitionKey attack_to_idle = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_ATTACK),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE) };
	TransitionKey dash_to_idle = { static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DASH),static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_IDLE) };
	TransitionKey any_to_exit{
		GetAnyStateID(motionStateMachine),
		GetExitStateID(motionStateMachine)
	};

	AddTransition(idle_to_moving, motionStateMachine);
	AddTransition(idle_to_air, motionStateMachine);
	AddTransition(idle_to_attack, motionStateMachine);
	AddTransition(idle_to_dash, motionStateMachine);
	AddTransition(moving_to_idle, motionStateMachine);
	AddTransition(moving_to_air, motionStateMachine);
	AddTransition(moving_to_dash, motionStateMachine);
	AddTransition(air_to_idle, motionStateMachine);
	AddTransition(air_to_attack, motionStateMachine);
	AddTransition(air_to_dash, motionStateMachine);
	AddTransition(damaged_to_idle, motionStateMachine);
	AddTransition(moving_to_attack, motionStateMachine);
	AddTransition(attack_to_idle, motionStateMachine);
	AddTransition(dash_to_idle, motionStateMachine);
	AddTransition(any_to_exit, motionStateMachine);
	AddTransitionFromAny(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DAMAGED), motionStateMachine);
	AddTransitionToExit(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DAMAGED), motionStateMachine);

	AddConditionToAnyTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DAMAGED), static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DAMAGED), motionStateMachine);
	AddConditionToExitTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DEAD), static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DAMAGED), motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DAMAGED), damaged_to_idle, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_MOVING), idle_to_moving, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_AIR), idle_to_air, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), idle_to_attack, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), idle_to_dash, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_MOVING), moving_to_idle, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_AIR), moving_to_air, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), moving_to_attack, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), moving_to_dash, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_AIR), air_to_idle, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), air_to_attack, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), air_to_dash, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), attack_to_idle, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), dash_to_idle, motionStateMachine);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_CLEAR), any_to_exit, motionStateMachine);

	SetBoolConditionForAnyTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DAMAGED), static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DAMAGED), true, motionStateMachine);
	SetBoolConditionForExitTransition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DEAD), static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE_DAMAGED), true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DAMAGED), damaged_to_idle, false, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_MOVING), idle_to_moving, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), idle_to_attack, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_AIR), idle_to_air, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), idle_to_dash, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_MOVING), moving_to_idle, false, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_AIR), moving_to_air, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), moving_to_attack, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), moving_to_dash, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_AIR), air_to_idle, false, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), air_to_attack, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), air_to_dash, true, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_ATTACKING), attack_to_idle, false, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DASHING), dash_to_idle, false, motionStateMachine);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_CLEAR), any_to_exit, true, motionStateMachine);
}

void PlayerStateComponent::Init()
{
	StateComponent::Init();

	isStageCleared_ = false;

	InnerStateMachine* motionStateMachine = new PlayerMotionState(stateMachine_, GetMessengerPtr());
	IState* deadState = new PlayerDeadState(stateMachine_, GetMessengerPtr(), this, this, playerView_.Injected());
	IState* stageClearState = new PlayerStageClearState(stateMachine_, GetMessengerPtr(), this, this, playerView_.Injected());

	AddState(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE), motionStateMachine, stateMachine_);
	AddState(static_cast<StateID>(PlayerStateType::STATE_DEAD), deadState, stateMachine_);
	AddState(static_cast<StateID>(PlayerStateType::STATE_STAGE_CLEAR), stageClearState, stateMachine_);

	AddBoolConditionInfo(static_cast<int>(PlayerConditionType::IS_DEAD), "isDead", false, stateMachine_);
	AddBoolConditionInfo(static_cast<int>(PlayerConditionType::IS_CLEAR), "isStageClear", false, stateMachine_);

	TransitionKey motion_to_dead = {
		static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE),
		static_cast<int>(PlayerStateType::STATE_DEAD)
	};
	TransitionKey motion_to_stageClear = {
		static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE),
		static_cast<int>(PlayerStateType::STATE_STAGE_CLEAR)
	};

	AddTransition(motion_to_dead, stateMachine_);
	AddTransition(motion_to_stageClear, stateMachine_);

	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::IS_DEAD), motion_to_dead, stateMachine_);
	AddConditionToTransition(static_cast<ConditionID>(PlayerConditionType::IS_CLEAR), motion_to_stageClear, stateMachine_);

	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::IS_DEAD), motion_to_dead, true, stateMachine_);
	SetBoolCondition(static_cast<ConditionID>(PlayerConditionType::IS_CLEAR), motion_to_stageClear, true, stateMachine_);


	if (motionStateMachine)
	{
		InitializeMotionStateMachine(motionStateMachine);
	}


	SetInitialState(static_cast<int>(PlayerStateType::STATE_MOTION_MACHINE), stateMachine_);
}

void PlayerStateComponent::Update()
{
	StateComponent::Update();
	stateMachine_->Update();
	Reset();
}

void PlayerStateComponent::Render()
{
	StateComponent::Render();
}

void PlayerStateComponent::Term()
{
	StateComponent::Term();
}

void PlayerStateComponent::HandleMessage(const IEventMessage& _msg)
{
	const HoriAxisInputMsg* horiAxisInputMsg = TypeidSystem::SafeCast<HoriAxisInputMsg>(&_msg);
	const JumpInputMsg* jumpInputMsg = TypeidSystem::SafeCast<JumpInputMsg>(&_msg);
	const ReleaseJumpInputMsg* releaseJumpInputMsg = TypeidSystem::SafeCast<ReleaseJumpInputMsg>(&_msg);
	const AttackInputMsg* attackInputMsg = TypeidSystem::SafeCast<AttackInputMsg>(&_msg);
	const DashInputMsg* dashInputMsg = TypeidSystem::SafeCast<DashInputMsg>(&_msg);
	const SwitchWeaponInputMsg* switchWeaponInput = TypeidSystem::SafeCast<SwitchWeaponInputMsg>(&_msg);
	const InteractInputMsg* interactInputMsg = TypeidSystem::SafeCast<InteractInputMsg>(&_msg);
	const StartStageClearSemMsg* startStageClearSemMsg = TypeidSystem::SafeCast<StartStageClearSemMsg>(&_msg);

	const SetIsDamagedConditionMsg* setIsDamagedConditionMsg = TypeidSystem::SafeCast<SetIsDamagedConditionMsg>(&_msg);
	const SetIsDeadConditionMsg* setIsDeadConditionMsg = TypeidSystem::SafeCast<SetIsDeadConditionMsg>(&_msg);
	const SetIsClearConditionMsg* setIsClearConditionMsg = TypeidSystem::SafeCast<SetIsClearConditionMsg>(&_msg);


	if (setIsDamagedConditionMsg)
	{
		if (!playerView_->IsInVincible())
		{
			InnerStateMachine* subStateMachine = nullptr;

			auto it = stateTable_.find(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE));

			if (it != stateTable_.end())
				subStateMachine = dynamic_cast<InnerStateMachine*>(it->second);

			if (subStateMachine)
				SetBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DAMAGED), setIsDamagedConditionMsg->GetValue(), subStateMachine);
			return;
		}
	}

	if (setIsDeadConditionMsg)
	{
		InnerStateMachine* subStateMachine = nullptr;

		auto it = stateTable_.find(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE));

		if (it != stateTable_.end())
			subStateMachine = dynamic_cast<InnerStateMachine*>(it->second);

		if (subStateMachine)
			SetBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_DEAD), setIsDeadConditionMsg->GetValue(), subStateMachine);
	}

	if (setIsClearConditionMsg)
	{
		InnerStateMachine* subStateMachine = nullptr;

		auto it = stateTable_.find(static_cast<StateID>(PlayerStateType::STATE_MOTION_MACHINE));

		if (it != stateTable_.end())
			subStateMachine = dynamic_cast<InnerStateMachine*>(it->second);

		if (subStateMachine)
			SetBoolConditionInfo(static_cast<ConditionID>(PlayerConditionType::MOTION_IS_CLEAR), setIsClearConditionMsg->GetValue(), subStateMachine);
	}

	if (startStageClearSemMsg)
	{
		isStageCleared_ = true;
	}

	if (dashInputMsg)
	{
		MarkSemanticInput(GameSemantic::Semantic::START_DASH);
	}

	if (horiAxisInputMsg)
	{
		SetInputCache({ horiAxisInputMsg->GetValue(),0.0f });

		MarkSemanticInput(GameSemantic::Semantic::START_MOVE);
	}
	else if (jumpInputMsg)
	{
		MarkSemanticInput(GameSemantic::Semantic::START_JUMP);
	}
	else if (releaseJumpInputMsg)
	{
		MarkSemanticInput(GameSemantic::Semantic::RELEASE_JUMP);
	}
	else if (attackInputMsg)
	{
		MarkSemanticInput(GameSemantic::Semantic::START_ATTACK);
	}
	else if (switchWeaponInput)
	{
		MarkSemanticInput(GameSemantic::Semantic::START_SWITCH_WEAPON);
	}else if (interactInputMsg)
	{
		MarkSemanticInput(GameSemantic::Semantic::START_INTERACT);
	}

}

void PlayerStateComponent::Reset()
{
	StateComponent::Reset();

	inputCacheForState = { 0.0f,0.0f };
}

Lib::Math::Vector2f PlayerStateComponent::GetInputCache() const
{
	return inputCacheForState;
}

bool PlayerStateComponent::IsStageCleared() const
{
	return isStageCleared_;
}

void PlayerStateComponent::SetInputCache(const Lib::Math::Vector2f& _inputCache)
{
	inputCacheForState = _inputCache;
}
