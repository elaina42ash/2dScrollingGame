#include "StateMachine/State/PlayerDamagedState.h"

PlayerDamagedState::PlayerDamagedState(IStateMachine* _parent, PlayerStateComponent* _playerStateComponent) : PlayerState(_parent, _playerStateComponent)
{
}

void PlayerDamagedState::Enter()
{
	PlayerState::Enter();
}

void PlayerDamagedState::Update()
{
	PlayerState::Update();
}

void PlayerDamagedState::Exit()
{
	PlayerState::Exit();
}
