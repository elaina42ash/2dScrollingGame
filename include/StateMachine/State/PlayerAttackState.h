#pragma once
#include "PlayerState.h"

class PlayerAttackState:public PlayerState
{
public:
	PlayerAttackState(IStateMachine* _parent, PlayerStateComponent* _playerStateComponent);

	void Enter() override;
	void Update() override;
	void Exit() override;
};