#include "StateMachine/State/Player/PlayerDeadState.h"

#include "Fwk/Framework.h"
#include "StateMachine/State/Player/PlayerStateDef.h"

PlayerDeadState::PlayerDeadState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent,
                                 IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView): PlayerState(_parent, _messenger, _playerStateComponent, _inputCacheProvider, _playView)
{
}

void PlayerDeadState::Enter()
{
	PlayerState::Enter();

	DebugLog("[enter state] player dead");

	timer_.Start(1.5f);
}

void PlayerDeadState::Update()
{
	PlayerState::Update();

	if (timer_.IsFinished())
	{
		parent_->SetBoolConditionInfo(static_cast<IStateMachine::ConditionID>(PlayerConditionType::IS_DEAD),false);
	}
}

void PlayerDeadState::Exit()
{
	PlayerState::Exit();

	DebugLog("[exit state] player dead");
}

IStateMachine* PlayerDeadState::AsStateMachine()
{
	return nullptr;
}
