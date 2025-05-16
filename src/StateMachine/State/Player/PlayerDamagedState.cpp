#include "StateMachine/State/Player/PlayerDamagedState.h"

#include "Event/Message/SemanticMsg/EndKnockBackSemMsg.h"
#include "Event/Message/SemanticMsg/StartHurtSemMsg.h"
#include "Event/Message/SemanticMsg/StartKnockBackSemMsg.h"
#include "Fwk/Framework.h"
#include "StateMachine/State/Player/PlayerStateDef.h"

PlayerDamagedState::PlayerDamagedState(IStateMachine* _parent, IMessenger* _messenger,
	IStateComponent* _playerStateComponent, IInputCacheProvider* _inputCacheProvider, IPlayerView* _playView) : PlayerState(_parent, _messenger, _playerStateComponent, _inputCacheProvider, _playView)
{
}

void PlayerDamagedState::Enter()
{
	PlayerState::Enter();

	DebugLog("[enter state] player damaged");

	StartHurtSemMsg msg(1);
	messenger_->SendMsg(msg);

	step_ = 0;

	timer_.Start(0.05f);
}

void PlayerDamagedState::Update()
{
	PlayerState::Update();

	switch (step_)
	{
	case 0: {
		StartKnockBackSemMsg msg;
		SendMsg(msg);

		if (timer_.IsFinished())
		{
			timer_.Reset();
			timer_.Start(0.05f);
			++step_;
		}
	}break;
	case 1: {
		if (timer_.IsFinished())
		{
			EndKnockBackSemMsg msg;
			SendMsg(msg);

			if (parent_)
			{
				parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_DAMAGED), false);
				return;
			}
		}
	}break;
	default:
		break;
	}
}

void PlayerDamagedState::Exit()
{
	PlayerState::Exit();

	DebugLog("[exit state] player damaged");

	parent_->SetBoolConditionInfo(static_cast<int>(PlayerConditionType::MOTION_IS_DAMAGED), false);
}
