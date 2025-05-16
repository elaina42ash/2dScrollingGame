#include "StateMachine/State/Player/PlayerDashState.h"

#include "Event/Message/SemanticMsg/EndDashSemMsg.h"
#include "Event/Message/SemanticMsg/StartDashSemMsg.h"
#include "StateMachine/State/Player/PlayerStateDef.h"

PlayerDashState::PlayerDashState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent,
	IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView) : PlayerState(_parent, _messenger, _playerStateComponent, _inputCacheProvider, _playView)
{
}

void PlayerDashState::Enter()
{
	PlayerState::Enter();

	StartDashSemMsg startDashSemMsg;
	SendMsg(startDashSemMsg);
	timer_.Start(0.1f);
}

void PlayerDashState::Update()
{
	PlayerState::Update();

	if (timer_.IsFinished())
	{
		parent_->SetBoolConditionInfo(static_cast<IStateMachine::ConditionID>(PlayerConditionType::MOTION_IS_DASHING), false);
	}
}

void PlayerDashState::Exit()
{
	PlayerState::Exit();
	EndDashSemMsg endDashSemMsg;
	SendMsg(endDashSemMsg);
}

IStateMachine* PlayerDashState::AsStateMachine()
{
	return nullptr;
}
