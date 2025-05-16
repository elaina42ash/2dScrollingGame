#pragma once
#include "PlayerState.h"

class PlayerDamagedState : public PlayerState
{
private:
	int step_ = 0;
	
public:
	PlayerDamagedState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent,
		IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView);

	void Enter() override;

	void Update() override;

	void Exit() override;
};
