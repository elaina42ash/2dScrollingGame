#pragma once
#include "PlayerState.h"

class PlayerAttackState : public PlayerState
{
public:
	PlayerAttackState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent,
		IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView);

	void Enter() override;

	void Update() override;

	void Exit() override;

	IStateMachine* AsStateMachine() override;
};
