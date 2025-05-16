#include "StateMachine/State/PlayerAttackState.h"

PlayerAttackState::PlayerAttackState(IStateMachine* _parent, PlayerStateComponent* _playerStateComponent): PlayerState(_parent, _playerStateComponent)
{
}

void PlayerAttackState::Enter()
{
	PlayerState::Enter();
}

void PlayerAttackState::Update()
{
	PlayerState::Update();
}

void PlayerAttackState::Exit()
{
	PlayerState::Exit();
}
