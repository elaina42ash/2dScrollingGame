#pragma once
#include <string>
#include <unordered_map>
#include "Component.h"
#include "Player.h"
#include "command/ICommand.h"
#include "Event/Messenger.h"
#include "Event/Listener/IMessageListener.h"
#include "Event/Message/IEventMessage.h"
#include "statemachine/IStateMachine.h"
#include "StateMachine/State/IState.h"

class PlayerStateComponent : public Component, public IMessageListener
{
	using StateID = int;
public:
	enum class BehaviourType {
		NONE = -1,
		START_MOVE = 1000,
		START_JUMP,
		RELEASE_JUMP,
	};

	enum class PhysicsEffectType {
		NONE = -1,
		START_GRAVITY = 1000,
		START_FRICTION
	};

	enum class PlayerConditionID
	{
		IS_DAMAGED

	};

	enum class PlayerStateID
	{
		NONE = -1,
		MOVE = 1000,	// 通常移動中
		ATTACK,			// 攻撃中
		DAMAGED,		// 被ダメージ中
		DYING,			// やられ中
		DEAD,			// やられた
		GOAL			// ゴール地点に到達した
	};


	struct PlayerTransitionKey
	{
		StateID from;
		StateID to;
		bool operator==(const PlayerTransitionKey& _other)
		{
			return  from == to;
		}
	};
private:
	IStateMachine* stateMachine_;

	std::unordered_map<BehaviourType, const ICommand*> semanticInputTable_;

	std::unordered_map<PlayerStateID, IState*> stateTable_;
	std::unordered_map<PlayerConditionID, std::string> conditionTable_;
	std::vector<PlayerTransitionKey> transitions_;

	Messenger* messenger_;
	Player* player_;
public:

	explicit  PlayerStateComponent(Messenger* _message, Player* _player);

	PlayerStateComponent(bool _isActive, Messenger* _messenger, Player* _player);

	~PlayerStateComponent() override;

	void Init() override;


	void Update() override;

	void  HandleMessage(const IEventMessage& _msg) override;

	bool HasInput(BehaviourType _type)const;

	const Messenger* GetMessenger() const;

	const ICommand* GetCommand(BehaviourType _type) const;

	const Player* GetPlayer() const;

private:

	void InitializeDefaults();

	void AddState(PlayerStateID _stateID, IState* _state);

	void RemoveState(PlayerStateID _stateID);

	void AddBoolCondition(PlayerConditionID _conditonID, const std::string& _name, bool _value);

	void AddIntCondition(PlayerConditionID _conditonID, const std::string& _name, int _value);

	void AddFloatCondition(PlayerConditionID _conditonID, const std::string& _name, float _value);

	void SetBoolCondition(PlayerConditionID _conditonID, bool _value);

	void SetIntCondition(PlayerConditionID _conditonID, int _value, int _compareTo, int _comp);

	void SetFloatCondition(PlayerConditionID _conditonID, float _value, float _compareTo, int _comp);

	const IFsmCondition* GetCondition(PlayerConditionID _conditionID);

	void AddConditionToTransition(PlayerConditionID _condition, const PlayerTransitionKey& _transitionID);

	void RemoveCondition(PlayerConditionID _conditionID);

	void RemoveConditionFromTransition(PlayerConditionID _conditionID, StateID _from, StateID _to);

	void AddTransition(const PlayerTransitionKey& _transitionID);

	void RemoveTransition(const PlayerTransitionKey& _transitionID);
};



