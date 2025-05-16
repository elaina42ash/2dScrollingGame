#include "Player.h"
#include "Component/PlayerPhysicsComponent.h"
#include "component/Component.h"
#include "component/PlayerStateComponent.h"
#include "Event/Message/PhysicsEffectMessage.h"
#include "Fwk/Framework.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(bool _isActive, Player* player) : ::Component(_isActive),player_(player)
{
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Player* player) : player_(player)
{
}

void PlayerPhysicsComponent::UpdateGravity()
{
	// 重力の倍率
	float gravityScale = 5.0f;
	// このフレームでの重力加速量。
	float gravity = -9.8f * Time_I->GetDeltaTime() * gravityScale;
	// このフレームでの最大重力
	float maxGravity = -1200.0f * Time_I->GetDeltaTime();
	// 重力の計算
	player_->SetVelocityY(player_->GetVelocityY() + gravity);
	if (player_->GetVelocityY() < maxGravity)
	{
		player_->SetVelocityY(maxGravity);
	}
}

void PlayerPhysicsComponent::Init()
{
	Component::Init();
	defaultPhysicsEffectFlagTable_ = {
	{PlayerStateComponent::PhysicsEffectType::NONE,false},
	{PlayerStateComponent::PhysicsEffectType::START_GRAVITY,true},
	{PlayerStateComponent::PhysicsEffectType::START_FRICTION,true},
	};
	Reset();
}

void PlayerPhysicsComponent::UpdateFriction()
{
	// 摩擦による速度の減衰
	{
		player_->SetVelocityX(player_->GetVelocityX() * 0.82f);
		// ある程度速度が小さくなったらゼロに丸めてしまってOK
		if (fabsf(player_->GetVelocityX()) < 0.001f)
		{
			player_->SetVelocityX(0.0f);
		}
	}
}

void PlayerPhysicsComponent::Update()
{
	Component::Update();

	if (GetFlag(PlayerStateComponent::PhysicsEffectType::START_GRAVITY))
		UpdateGravity();
	if (GetFlag(PlayerStateComponent::PhysicsEffectType::START_FRICTION))
		UpdateFriction();



	Reset();
}

void PlayerPhysicsComponent::HandleMessage(const IEventMessage& _msg)
{
	if (_msg.GetMessageType() == IEventMessage::MessageType::EFFECT)
	{
		const PhysicsEffectMessage* effectMsg = TypeidSystem::SafeCast<PhysicsEffectMessage>(&_msg);

		if (!effectMsg)
			return;


		/*if (effectMsg->GetPhysicsEffectType() == PhysicsEffectType::GRAVITY)
		{
			SetFlag(PhysicsEffectType::GRAVITY, true);
		}*/

	}
}

void PlayerPhysicsComponent::SetFlag(PlayerStateComponent::PhysicsEffectType _physicsEffect, bool _flag)
{
	auto it = physicsEffectFlagTable_.find(_physicsEffect);
	if (it == physicsEffectFlagTable_.end())
	{
		physicsEffectFlagTable_.insert({ _physicsEffect,_flag });
		return;
	}

	it->second = _flag;
}

bool PlayerPhysicsComponent::GetFlag(PlayerStateComponent::PhysicsEffectType _physicsEffect)
{
	auto it = physicsEffectFlagTable_.find(_physicsEffect);
	if (it == physicsEffectFlagTable_.end())
		return false;
	return it->second;
}

void PlayerPhysicsComponent::InitializeDefaults()
{


}

void PlayerPhysicsComponent::Reset()
{
	physicsEffectFlagTable_ = defaultPhysicsEffectFlagTable_;
}
