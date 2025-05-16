#include "StateMachine/State/Player/PlayerAttackState.h"
#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"
#include "Event/Message/SemanticMsg/StopJumpSemMsg.h"
#include "Fwk/Framework.h"
#include "StateMachine/State/Player/PlayerStateDef.h"

PlayerAttackState::PlayerAttackState(IStateMachine* _parent, IMessenger* _messenger,
	IStateComponent* _playerStateComponent, IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView) : PlayerState(_parent, _messenger, _playerStateComponent, _inputCacheProvider, _playView)
{
}

void PlayerAttackState::Enter()
{
	PlayerState::Enter();

	DebugLog("[enter state] player attack");

	StartAttackSemMsg startAttackSemMsg;
	SendMsg(startAttackSemMsg);
}

void PlayerAttackState::Update()
{
	if (!playerView_->IsAttacking())
	{
		parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_ATTACKING), false);
		return;
	}
}

void PlayerAttackState::Exit()
{
	PlayerState::Exit();

	DebugLog("[exit state] player attack");

	parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_ATTACKING), false);
}

IStateMachine* PlayerAttackState::AsStateMachine()
{
	return nullptr;
}
