#include "component/PlayerStateComponent.h"
#include "Command/ReleaseJumpIntentCommand.h"
#include "command/StartJumpIntentCommand.h"
#include "command/StartMoveIntentCommand.h"
#include "Event/Message/ChangeBoolConditionMessage.h"
#include "Event/Message/ChangeFloatConditionMessage.h"
#include "Event/Message/ChangeIntConditionMessage.h"
#include "Event/Message/InputMessage.h"
#include "StateMachine/StateMachine.h"
#include "StateMachine/Condition/FloatCondition.h"
#include "StateMachine/Condition/IntCondition.h"
#include "StateMachine/State/PlayerDamagedState.h"
#include "statemachine/state/PlayerMoveState.h"

void PlayerStateComponent::InitializeDefaults()
{
	stateMachine_ = new StateMachine();
}

void PlayerStateComponent::AddState(PlayerStateID _stateID, IState* _state)
{
	auto it = stateTable_.find(_stateID);
	if (it != stateTable_.end())
		return;
	stateTable_.insert({ _stateID ,_state });
	stateMachine_->AddState(static_cast<int>(_stateID), _state);
}

void PlayerStateComponent::RemoveState(PlayerStateID _stateID)
{
	auto it = stateTable_.find(_stateID);
	if (it == stateTable_.end())
		return;
	stateMachine_->RemoveState(static_cast<int>(_stateID));
	stateTable_.erase(it);
}

void PlayerStateComponent::AddBoolCondition(PlayerConditionID _conditonID, const std::string& _name, bool _value)
{

	auto it = conditionTable_.find(_conditonID);
	if (it != conditionTable_.end())
		return;
	conditionTable_.insert({ _conditonID ,_name });
	int id = static_cast<int>(_conditonID);
	stateMachine_->AddBoolCondition(id, _value);
}

void PlayerStateComponent::AddIntCondition(PlayerConditionID _conditonID, const std::string& _name, int _value)
{

	auto it = conditionTable_.find(_conditonID);
	if (it != conditionTable_.end())
		return;
	conditionTable_.insert({ _conditonID ,_name });
	int id = static_cast<int>(_conditonID);
	stateMachine_->AddIntCondition(id, _value);
}

void PlayerStateComponent::AddFloatCondition(PlayerConditionID _conditonID, const std::string& _name, float _value)
{

	auto it = conditionTable_.find(_conditonID);
	if (it != conditionTable_.end())
		return;
	conditionTable_.insert({ _conditonID ,_name });
	int id = static_cast<int>(_conditonID);
	stateMachine_->AddFloatCondition(id, _value);
}

void PlayerStateComponent::SetBoolCondition(PlayerConditionID _conditonID, bool _value)
{
	int id = static_cast<int>(_conditonID);
	stateMachine_->SetBoolCondition(id, _value);
}

void PlayerStateComponent::SetIntCondition(PlayerConditionID _conditonID, int _value, int _compareTo, int _comp)
{
	int id = static_cast<int>(_conditonID);
	stateMachine_->SetIntCondition(id, _value, _compareTo, _comp);
}

void PlayerStateComponent::SetFloatCondition(PlayerConditionID _conditonID, float _value, float _compareTo, int _comp)
{
	int id = static_cast<int>(_conditonID);
	stateMachine_->SetFloatCondition(id, _value, _compareTo, _comp);
}

const IFsmCondition* PlayerStateComponent::GetCondition(PlayerConditionID _conditionID)
{
	int id = static_cast<int>(_conditionID);
	const IFsmCondition* condition = stateMachine_->GetCondition(id);
	return  condition;
}

void PlayerStateComponent::AddConditionToTransition(PlayerConditionID _condition, const PlayerTransitionKey& _transitionID)
{
	stateMachine_->AddConditionToTransition(static_cast<int>(_condition), _transitionID.from, _transitionID.to);
}

void PlayerStateComponent::RemoveCondition(PlayerConditionID _conditionID)
{
	stateMachine_->RemoveCondition(static_cast<int>(_conditionID));
	conditionTable_.erase(_conditionID);
}

void PlayerStateComponent::RemoveConditionFromTransition(PlayerConditionID _conditionID, StateID _from, StateID _to)
{
	stateMachine_->RemoveConditionFromTransition(static_cast<int>(_conditionID), _from, _to);
}

void PlayerStateComponent::AddTransition(const PlayerTransitionKey& _transitionID)
{
	auto it = std::find_if(transitions_.begin(), transitions_.end(), [_transitionID](const PlayerTransitionKey& t)
		{
			return _transitionID.from == t.from && _transitionID.to == t.to;
		});
	if (it != transitions_.end())
		return;
	transitions_.push_back(_transitionID);
	stateMachine_->AddTransition(_transitionID.from, _transitionID.to);
}

void PlayerStateComponent::RemoveTransition(const PlayerTransitionKey& _transitionID)
{
	auto it = std::find_if(transitions_.begin(), transitions_.end(), [_transitionID](const PlayerTransitionKey& t)
		{
			return _transitionID.from == t.from && _transitionID.to == t.to;
		});
	if (it == transitions_.end())
		return;
	transitions_.erase(std::remove_if(transitions_.begin(), transitions_.end(), [_transitionID](const PlayerTransitionKey& t)
		{
			return _transitionID.from == t.from && _transitionID.to == t.to;
		}), transitions_.end()
			);
	stateMachine_->RemoveTransition(_transitionID.from, _transitionID.to);
}


PlayerStateComponent::PlayerStateComponent(Messenger* _message, Player* _player) :messenger_(_message), player_(_player)
{
	InitializeDefaults();
}

PlayerStateComponent::PlayerStateComponent(bool _isActive, Messenger* _messenger, Player* _player) : Component(_isActive), messenger_(_messenger), player_(_player)
{
	InitializeDefaults();
}

PlayerStateComponent::~PlayerStateComponent()
{
	delete stateMachine_;
}

void PlayerStateComponent::Init()
{

	PlayerMoveState* moveState = new PlayerMoveState(stateMachine_, this);
	PlayerDamagedState* damagedState = new PlayerDamagedState(stateMachine_, this);

	AddState(PlayerStateID::MOVE, moveState);
	AddState(PlayerStateID::DAMAGED, damagedState);

	AddBoolCondition(PlayerConditionID::IS_DAMAGED, "isDamaged", false);

	PlayerTransitionKey moveToDamagedTransitionID = {
		static_cast<StateID>(PlayerStateID::MOVE),
		static_cast<StateID>(PlayerStateID::DAMAGED)
	};

	AddConditionToTransition(PlayerConditionID::IS_DAMAGED, moveToDamagedTransitionID);

	stateMachine_->SetInitialState(static_cast<int>(PlayerStateID::MOVE));
}

void PlayerStateComponent::Update()
{
	stateMachine_->Update();
	Reset();
}

void PlayerStateComponent::HandleMessage(const IEventMessage& _msg)
{
	if (_msg.GetMessageType() == IEventMessage::MessageType::INPUT)
	{

		const InputMessage* inputMsg = TypeidSystem::SafeCast<InputMessage>(&_msg);

		const ICommand* command = inputMsg->GetCommand();
		if (!command)
			return;

		const StartMoveIntentCommand* startMoveIntentCommand = TypeidSystem::SafeCast<StartMoveIntentCommand>(command);
		const StartJumpIntentCommand* startJumpIntentCommand = TypeidSystem::SafeCast<StartJumpIntentCommand>(command);
		const ReleaseJumpIntentCommand* releaseJumpIntentCommand = TypeidSystem::SafeCast<ReleaseJumpIntentCommand>(command);


		if (startMoveIntentCommand)
			semanticInputTable_[BehaviourType::START_MOVE] = inputMsg->GetCommand();
		if (startJumpIntentCommand)
			semanticInputTable_[BehaviourType::START_JUMP] = inputMsg->GetCommand();
		if (releaseJumpIntentCommand)
			semanticInputTable_[BehaviourType::RELEASE_JUMP] = inputMsg->GetCommand();

	}
	else if (_msg.GetMessageType() == IEventMessage::MessageType::CHANGE_CONDITION)
	{
		const ChangeBoolConditionMessage* changeBoolConditionMsg = TypeidSystem::SafeCast<ChangeBoolConditionMessage>(&_msg);
		const ChangeIntConditionMessage* changeIntConditionMsg = TypeidSystem::SafeCast<ChangeIntConditionMessage>(&_msg);
		const ChangeFloatConditionMessage* changeFloatConditionMsg = TypeidSystem::SafeCast<ChangeFloatConditionMessage>(&_msg);


		if (changeBoolConditionMsg)
		{
			ChangeBoolConditionMessageInternal::ChangeBoolConditionMessageParams params = changeBoolConditionMsg->GetParams();
			SetBoolCondition(params.conditionID, params.value);
		}
		if (changeIntConditionMsg)
		{
			ChangeIntConditionMessageInternal::ChangeIntConditionMessageParams params = changeIntConditionMsg->GetParams();
			const IFsmCondition* oldCondition = GetCondition(params.conditionID);
			const IntCondition* oldIntCondition = TypeidSystem::SafeCast<IntCondition>(oldCondition);
			SetIntCondition(params.conditionID, params.value, oldIntCondition->GetCompareTo(), static_cast<int>(oldIntCondition->GetComparator()));
		}
		if (changeFloatConditionMsg)
		{
			ChangeFloatConditionMessageInternal::ChangeFloatConditionMessageParams params = changeFloatConditionMsg->GetParams();
			const IFsmCondition* oldCondition = GetCondition(params.conditionID);
			const FloatCondition* oldFloatCondition = TypeidSystem::SafeCast<FloatCondition>(oldCondition);
			SetFloatCondition(params.conditionID, params.value, oldFloatCondition->GetCompareTo(), static_cast<int>(oldFloatCondition->GetComparator()));
		}


	}
}

bool PlayerStateComponent::HasInput(BehaviourType _type) const
{
	auto it = semanticInputTable_.find(_type);
	if (it == semanticInputTable_.end() || it->second == nullptr)
		return false;
	return true;
}

const Messenger* PlayerStateComponent::GetMessenger() const
{
	return messenger_;
}

const ICommand* PlayerStateComponent::GetCommand(BehaviourType _type) const
{
	auto it = semanticInputTable_.find(_type);
	if (it != semanticInputTable_.end())
		return it->second;
	return nullptr;
}

const Player* PlayerStateComponent::GetPlayer() const
{
	return player_;
}


