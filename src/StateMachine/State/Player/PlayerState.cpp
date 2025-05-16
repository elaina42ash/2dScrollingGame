#include "statemachine/state/Player/PlayerState.h"
PlayerState::PlayerState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent,
	IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView) : State(_parent, _messenger),
	playerStateComponent_(_playerStateComponent),
	inputCacheProvider_(_inputCacheProvider),
	playerView_(_playView)
{
}

void PlayerState::Enter()
{
	State::Enter();
}

void PlayerState::Update()
{
	State::Update();
}

void PlayerState::Exit()
{
	State::Exit();
}

IStateMachine* PlayerState::AsStateMachine()
{
	return nullptr;
}
