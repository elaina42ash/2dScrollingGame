#pragma once
#include "StateMachine/State/Player/PlayerState.h"

class PlayerDeadState : public PlayerState
{
public:
	PlayerDeadState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent,
		IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView);

	void Enter() override;

	void Update() override;

	void Exit() override;

	IStateMachine* AsStateMachine() override;
};
