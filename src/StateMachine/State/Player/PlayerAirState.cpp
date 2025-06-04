#include "StateMachine/State/Player/PlayerAirState.h"

#include "Component/Player/DecisionLogicalComponent/Class/PlayerStateComponent.h"
#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"
#include "Event/Message/SemanticMsg/StartSwitchWeaponSemMsg.h"
#include "Event/Message/SemanticMsg/StopJumpSemMsg.h"
#include "Fwk/Framework.h"
#include "StateMachine/State/Player/PlayerStateDef.h"

PlayerAirState::PlayerAirState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent, IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView) : PlayerState(_parent, _messenger, _playerStateComponent, _inputCacheProvider, _playView)
{
}

void PlayerAirState::Enter()
{
	PlayerState::Enter();

	DebugLog("[enter state] player air");

}

void PlayerAirState::Exit()
{
	PlayerState::Exit();

	DebugLog("[exit state] player air");

	parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_AIR), false);
}

void PlayerAirState::Update()
{
	PlayerState::Update();

	if (playerView_->GetVelocityY() <= 0 && playerView_->Grounded())
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_AIR),false);
		return;
	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_DASH))
	{
		PlayerStateComponent* stateComponent = dynamic_cast<PlayerStateComponent*>(playerStateComponent_.Injected());
		if (stateComponent&&!stateComponent->IsDashCooldown())
		{
			parent_->SetBoolConditionInfo(static_cast<IStateMachine::ConditionID>(PlayerConditionType::MOTION_IS_DASHING), true);
			return;
		}

	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_ATTACK))
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_ATTACKING), true);
		return;
	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::RELEASE_JUMP))
	{
		StopJumpSemMsg releaseJumpSemMsg;
		SendMsg(releaseJumpSemMsg);
	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_MOVE))
	{
		StartMoveSemMsg startMoveSemMsg(inputCacheProvider_->GetInputCache());
		SendMsg(startMoveSemMsg);
	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_SWITCH_WEAPON))
	{
		StartSwitchWeaponSemMsg startSwitchWeaponSemMsg;
		SendMsg(startSwitchWeaponSemMsg);
	}
}


