#pragma once
#include "Component/PlayerStateComponent.h"
using PhysicsEffectFlag = bool;
class Player;
class PlayerPhysicsComponent :public Component, public IMessageListener
{
private:
	std::unordered_map<PlayerStateComponent::PhysicsEffectType, PhysicsEffectFlag> physicsEffectFlagTable_;
	std::unordered_map<PlayerStateComponent::PhysicsEffectType, PhysicsEffectFlag> defaultPhysicsEffectFlagTable_;

	Player* player_;
public:
	PlayerPhysicsComponent(bool _isActive, Player* player);

	explicit PlayerPhysicsComponent(Player* player);

	void Init() override;
	void Update() override;
	void HandleMessage(const IEventMessage& _msg) override;

private:
	void SetFlag(PlayerStateComponent::PhysicsEffectType _physicsEffect, bool _flag);

	bool GetFlag(PlayerStateComponent::PhysicsEffectType _physicsEffect);

	void InitializeDefaults();

	void Reset() override;

	void UpdateGravity();

	void UpdateFriction();
};


