#include "StateMachine\State/Player/PlayerStageClearState.h"

#include "Event/Message/SemanticMsg/StartStageClearSemMsg.h"
#include "Fwk/Framework.h"

PlayerStageClearState::PlayerStageClearState(IStateMachine* _parent, IMessenger* _messenger,
	IStateComponent* _playerStateComponent, IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView) : PlayerState(_parent, _messenger, _playerStateComponent, _inputCacheProvider, _playView)
{
}

void PlayerStageClearState::Enter()
{
	PlayerState::Enter();

	DebugLog("[enter state] player clear");

	StartStageClearSemMsg startStageClearSemMsg;
	SendMsg(startStageClearSemMsg);
}

void PlayerStageClearState::Update()
{
	PlayerState::Update();
}

void PlayerStageClearState::Exit()
{
	PlayerState::Exit();

	DebugLog("[exit state] player clear");
}

IStateMachine* PlayerStageClearState::AsStateMachine()
{
	return nullptr;
}
