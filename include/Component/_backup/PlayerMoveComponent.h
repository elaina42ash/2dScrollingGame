#pragma once
#include <unordered_map>
#include "Component.h"
#include "GameDef.h"
#include "Event/Listener/IMessageListener.h"
#include "Lib/Math/TVector2.h"
#include "Component/PlayerStateComponent.h"

using BehaviourFlag = bool;

class Player;
class PlayerMoveComponent : public Component, public IMessageListener
{
public:
	PlayerMoveComponent(bool _isActive, Player* _player, Messenger* _messenger);

	PlayerMoveComponent(Player* _player, Messenger* _messenger);

	void UpdateDirection(const Lib::Math::Vector2f _moveInput);
	void Init() override;
	void SendTranslateAnimationRequest(const Lib::Math::Vector2f& _moveInput, const Direction& _direction);
	void Update() override;

	void HandleMessage(const IEventMessage& _msg) override;
private:
	Player* player_;

	std::unordered_map<PlayerStateComponent::BehaviourType, BehaviourFlag> behaviourFlagTable_;
	std::unordered_map<PlayerStateComponent::BehaviourType, BehaviourFlag> defaultBehaviourFlagTable_;

	Lib::Math::Vector2f moveInput;
	Messenger* messenger_;

private:
	void SetFlag(PlayerStateComponent::BehaviourType _behaviour, bool _flag);

	bool GetFlag(PlayerStateComponent::BehaviourType _behaviour);

	// 速度を更新する
	void UpdateVelocity(Lib::Math::Vector2f vInput);

	// 速度を用いて平行移動させる
	void Translate(Lib::Math::Vector2f vMove);

	void Reset() override;
	void InitializeDefaults();

	bool GroundCheck(const Lib::Math::Vector2f& _position);
};

