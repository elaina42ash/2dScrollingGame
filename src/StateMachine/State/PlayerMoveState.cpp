#include "statemachine/state/PlayerMoveState.h"
#include "command/StartMoveIntentCommand.h"
#include "Event/Message/BehaviourMessage.h"

PlayerMoveState::PlayerMoveState(IStateMachine* _parent, PlayerStateComponent* _playerStateComponent) : PlayerState(_parent, _playerStateComponent)
{
}

void PlayerMoveState::Enter()
{
	PlayerState::Enter();
}

void PlayerMoveState::Update()
{
	PlayerState::Update();

	if (playerStateComponent_->HasInput(PlayerStateComponent::BehaviourType::START_MOVE))
	{
		const StartMoveIntentCommand* cmd = TypeidSystem::SafeCast<StartMoveIntentCommand>(playerStateComponent_->GetCommand(PlayerStateComponent::BehaviourType::START_MOVE));

		BehaviourMessage::BehaviourMessageParams params = {
			PlayerStateComponent::BehaviourType::START_MOVE,
		cmd->GetMoveInput(),
		};
		BehaviourMessage behaviourMessage(params);
		playerStateComponent_->GetMessenger()->SendMSG(behaviourMessage);
	}

	if (playerStateComponent_->HasInput(PlayerStateComponent::BehaviourType::START_JUMP))
	{
		BehaviourMessage::BehaviourMessageParams params = {
			PlayerStateComponent::BehaviourType::START_JUMP,
		};
		BehaviourMessage behaviourMessage(params);
		playerStateComponent_->GetMessenger()->SendMSG(behaviourMessage);
	}

	if (playerStateComponent_->HasInput(PlayerStateComponent::BehaviourType::RELEASE_JUMP))
	{
		BehaviourMessage::BehaviourMessageParams params = {
	PlayerStateComponent::BehaviourType::RELEASE_JUMP,
		};
		BehaviourMessage behaviourMessage(params);
		playerStateComponent_->GetMessenger()->SendMSG(behaviourMessage);
	}
}

void PlayerMoveState::Exit()
{
	PlayerState::Exit();
}
