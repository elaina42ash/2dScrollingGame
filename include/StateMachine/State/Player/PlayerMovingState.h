#pragma once
#include "PlayerState.h"

class PlayerMovingState : public PlayerState
{
public:
	PlayerMovingState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent,
		IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView);

	void Enter() override;

	void Update() override;

	void Exit() override;
};
