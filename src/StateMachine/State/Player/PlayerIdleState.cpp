#include "StateMachine/State/Player/PlayerIdleState.h"

#include "Event/Message/SemanticMsg/StartIdleSemMsg.h"
#include "Event/Message/SemanticMsg/StartJumpSemMsg.h"
#include "Fwk/Framework.h"
#include "StateMachine/State/Player/PlayerStateDef.h"

PlayerIdleState::PlayerIdleState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent,
	IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView): PlayerState(_parent, _messenger, _playerStateComponent, _inputCacheProvider, _playView)
{
}

void PlayerIdleState::Enter()
{
	PlayerState::Enter();

	DebugLog("[enter state] player idle");

	if (!playerView_->Grounded())
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_AIR), true);
		return;
	}

	StartIdleSemMsg startIdleSemMsg;
	SendMsg(startIdleSemMsg);
}

void PlayerIdleState::Exit()
{
	PlayerState::Exit();

	DebugLog("[exit state] player idle");

}

void PlayerIdleState::Update()
{
	PlayerState::Update();

	if (!playerView_->Grounded())
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_AIR), true);
		return;
	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_DASH))
	{
		parent_->SetBoolConditionInfo(static_cast<IStateMachine::ConditionID>(PlayerConditionType::MOTION_IS_DASHING), true);
		return;
	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_ATTACK))
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_ATTACKING), true);
		return;
	}

	if (playerView_->Grounded() && playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_JUMP))
	{
		StartJumpSemMsg startJumpSemMsg;
		SendMsg(startJumpSemMsg);
	}

	if (playerStateComponent_->IsSemanticInputTriggered(GameSemantic::Semantic::START_MOVE))
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_MOVING), true);
		return;
	}


}
