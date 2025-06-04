#include "StateMachine/State/Player/PlayerMovingState.h"
#include "GameMath.h"
#include "Component/Player/DecisionLogicalComponent/Class/PlayerStateComponent.h"
#include "Event/Message/SemanticMsg/StartJumpSemMsg.h"
#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"
#include "Event/Message/SemanticMsg/StartSwitchWeaponSemMsg.h"
#include "Fwk/Framework.h"
#include "StateMachine/State/Player/PlayerStateDef.h"
PlayerMovingState::PlayerMovingState(IStateMachine* _parent, IMessenger* _messenger,
	IStateComponent* _playerStateComponent, IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView) : PlayerState(_parent, _messenger, _playerStateComponent, _inputCacheProvider, _playView)
{
}

void PlayerMovingState::Exit()
{
	PlayerState::Exit();

	DebugLog("[exit state] player moving");

	parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_MOVING), false);
}



void PlayerMovingState::Enter()
{
	PlayerState::Enter();

	DebugLog("[enter state] player moving");


	StartMoveSemMsg startMoveSemMsg(inputCacheProvider_->GetInputCache());
	SendMsg(startMoveSemMsg);


}

void PlayerMovingState::Update()
{
	PlayerState::Update();


	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_ATTACK))
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_ATTACKING), true);
		return;
	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_DASH))
	{
		PlayerStateComponent* stateComponent = dynamic_cast<PlayerStateComponent*>(playerStateComponent_.Injected());
		if (stateComponent && !stateComponent->IsDashCooldown())
		{
			parent_->SetBoolConditionInfo(static_cast<IStateMachine::ConditionID>(PlayerConditionType::MOTION_IS_DASHING), true);
			return;
		}

	}

	if (!playerView_->Grounded())
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_AIR), true);
		return;
	}

	if (GameMath::FloatIsZero(playerView_->GetVelocityX()))
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_MOVING), false);
		return;
	}

	if (playerView_->Grounded() && playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_JUMP))
	{
		StartJumpSemMsg startJumpSemMsg;
		SendMsg(startJumpSemMsg);
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
