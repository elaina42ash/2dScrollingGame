#pragma once
#include "PlayerState.h"

class PlayerMoveState:public PlayerState
{
public:
	PlayerMoveState(IStateMachine* _parent, PlayerStateComponent* _playerStateComponent);

	void Enter() override;

	void Update() override;

	void Exit() override;
};
