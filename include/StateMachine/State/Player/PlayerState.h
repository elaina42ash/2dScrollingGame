#pragma once
#include "IInputCacheProvider .h"
#include "Component/Common/DecisionLogicalComponent/Interface/IStateComponent.h"
#include "Player/IPlayerView.h"
#include "StateMachine/State/State.h"


class PlayerState : public State
{
protected:
	Inject<IStateComponent> playerStateComponent_;
	Inject<IInputCacheProvider> inputCacheProvider_;
	Inject<IPlayerView> playerView_;
public:
	PlayerState(IStateMachine* _parent, IMessenger* _messenger, IStateComponent* _playerStateComponent, IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView);

	void Enter() override;

	void Update() override;

	void Exit() override;

	IStateMachine* AsStateMachine() override;
};

