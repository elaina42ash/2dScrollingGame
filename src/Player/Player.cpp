#include "Player/Player.h"
#include "Component/Player/DecisionLogicalComponent/Class/PlayerStateComponent.h"
#include "Component/Player/ExecutorComponent/Class/PlayerAnimationComponent.h"
#include "Component/Player/ExecutorComponent/Class/PlayerCombatStatusComponent.h"
#include "Component/Player/ExecutorComponent/Class/PlayerEquipmentComponent.h"
#include "Component/Player/ExecutorComponent/Class/PlayerHealthComponent.h"
#include "Component/Player/ExecutorComponent/Class/PlayerMovementComponent.h"
#include "Component/Player/ExecutorComponent/Class/PlayerPhysicsComponent.h"
#include "Component/Player/ExecutorComponent/Class/PlayerSoundComponent.h"
#include "Component/Player/ExecutorComponent/Class/PlayerTransformComponent.h"
#include "Component/Player/InputLogicalComponent/Class/PlayerInputComponent.h"
#include "Component/Player/SensorLogicalComponent/Class/PlayerCollisionComponent.h"
#include "Component/Player/SensorLogicalComponent/Class/PlayerGroundSensorComponent.h"
#include "Component/Player/SensorLogicalComponent/Class/PlayerTileMapSensorComponent.h"
#include "Event/Message/LogicalInputMsg/AttackInputMsg.h"
#include "Event/Message/LogicalInputMsg/DashInputMsg.h"
#include "Event/Message/LogicalInputMsg/HoriAxisInputMsg.h"
#include "Event/Message/LogicalInputMsg/JumpInputMsg.h"
#include "Event/Message/LogicalInputMsg/ReleaseJumpInputMsg.h"
#include "Event/Message/SemanticMsg/EndDashSemMsg.h"
#include "Event/Message/SemanticMsg/EndKnockBackSemMsg.h"
#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "Event/Message/SemanticMsg/StartDashSemMsg.h"
#include "Event/Message/SemanticMsg/StartHurtSemMsg.h"
#include "Event/Message/SemanticMsg/StartIdleSemMsg.h"
#include "Event/Message/SemanticMsg/StartJumpSemMsg.h"
#include "Event/Message/SemanticMsg/StartKnockBackSemMsg.h"
#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"
#include "Event/Message/SemanticMsg/StartStageClearSemMsg.h"
#include "Event/Message/SemanticMsg/StopJumpSemMsg.h"
#include "Event/Message/StateMsg/SetIsClearConditionMsg.h"
#include "Event/Message/StateMsg/SetIsDamagedConditionMsg.h"
#include "Event/Message/StateMsg/SetIsDeadConditionMsg.h"

Player::Player()
{
	
	transformComponent_ = new PlayerTransformComponent(true,&messenger_);
	AddComponent<ITransformComponent>(transformComponent_);

	tileMapSensorComponent_ = new PlayerTileMapSensorComponent(true, &messenger_);
	AddComponent<ITileMapSensorComponent>(tileMapSensorComponent_);

	groundSensorComponent_ = new PlayerGroundSensorComponent(true, &messenger_, this);
	AddComponent<IGroundSensorComponent>(groundSensorComponent_);

	collisionComponent_ = new PlayerCollisionComponent(true, &messenger_, this);
	AddComponent<ICollisionComponent>(collisionComponent_);

	animationComponent_ = new PlayerAnimationComponent(true, &messenger_, this);
	AddComponent<IAnimationComponent>(animationComponent_);

	inputComponent_ = new PlayerInputComponent(true, &messenger_);
	AddComponent<IInputComponent>(inputComponent_);

	stateComponent_ = new PlayerStateComponent(true, &messenger_, this);
	AddComponent<IStateComponent>(stateComponent_);

	physicsComponent_ = new PlayerPhysicsComponent(true, this, &messenger_);
	AddComponent<IPhysicsComponent>(physicsComponent_);

	movementComponent_ = new PlayerMovementComponent(true, this, &messenger_);
	AddComponent<IMovementComponent>(movementComponent_);

	soundComponent_ = new PlayerSoundComponent(true, &messenger_);
	AddComponent<ISoundComponent>(soundComponent_);

	equipmentComponent_ = new PlayerEquipmentComponent(true, this, this, &messenger_);
	AddComponent<IEquipmentComponent>(equipmentComponent_);

	combatStatusComponent_ = new PlayerCombatStatusComponent(true, &messenger_);
	AddComponent<ICombatStatusComponent>(combatStatusComponent_);

	healthComponent_ = new PlayerHealthComponent(true, &messenger_);
	AddComponent<IHealthComponent>(healthComponent_);
}

Player::~Player()
{
	if (inputComponent_)
	{
		delete inputComponent_;
		inputComponent_ = nullptr;
	}

	if (tileMapSensorComponent_)
	{
		delete tileMapSensorComponent_;
		tileMapSensorComponent_ = nullptr;
	}

	if (groundSensorComponent_)
	{
		delete groundSensorComponent_;
		groundSensorComponent_ = nullptr;
	}

	if (stateComponent_)
	{
		delete stateComponent_;
		stateComponent_ = nullptr;
	}

	if (equipmentComponent_)
	{
		delete equipmentComponent_;
		equipmentComponent_ = nullptr;
	}

	if (healthComponent_)
	{
		delete healthComponent_;
		healthComponent_ = nullptr;
	}

	if (transformComponent_)
	{
		delete transformComponent_;
		transformComponent_ = nullptr;
	}

	if (physicsComponent_)
	{
		delete physicsComponent_;
		physicsComponent_ = nullptr;
	}

	if (movementComponent_)
	{
		delete movementComponent_;
		movementComponent_ = nullptr;
	}

	if (combatStatusComponent_)
	{
		delete combatStatusComponent_;
		combatStatusComponent_ = nullptr;
	}

	if (collisionComponent_)
	{
		delete collisionComponent_;
		collisionComponent_ = nullptr;
	}

	if (animationComponent_)
	{
		delete animationComponent_;
		animationComponent_ = nullptr;
	}

	if (soundComponent_)
	{
		delete soundComponent_;
		soundComponent_ = nullptr;
	}
}

void Player::StateComponentSubscribeMsg()
{
	messenger_.Subscribe(TypeidSystem::GetTypeID<DashInputMsg>(), stateComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<HoriAxisInputMsg>(), stateComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<JumpInputMsg>(), stateComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<ReleaseJumpInputMsg>(), stateComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<AttackInputMsg>(), stateComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<SetIsDamagedConditionMsg>(), stateComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<SetIsDeadConditionMsg>(), stateComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<SetIsClearConditionMsg>(), stateComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartStageClearSemMsg>(), stateComponent_);
}

void Player::Init()
{
	GameObject::Init();

	SetComponentPriority<ITransformComponent>(0);
	SetComponentPriority<ITileMapSensorComponent>(1);
	SetComponentPriority<IGroundSensorComponent>(2);
	SetComponentPriority<ICollisionComponent>(3);
	SetComponentPriority<IAnimationComponent>(4);
	SetComponentPriority<IInputComponent>(5);
	SetComponentPriority<IStateComponent>(6);
	SetComponentPriority<IPhysicsComponent>(7);
	SetComponentPriority<IMovementComponent>(8);
	SetComponentPriority<ISoundComponent>(9);
	SetComponentPriority<IEquipmentComponent>(10);
	SetComponentPriority<ICombatStatusComponent>(11);
	SetComponentPriority<IHealthComponent>(12);

	messenger_.Subscribe(TypeidSystem::GetTypeID<StartHurtSemMsg>(), healthComponent_);

	messenger_.Subscribe(TypeidSystem::GetTypeID<StartKnockBackSemMsg>(), collisionComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<EndKnockBackSemMsg>(), collisionComponent_);

	StateComponentSubscribeMsg();

	messenger_.Subscribe(TypeidSystem::GetTypeID<StartAttackSemMsg>(), equipmentComponent_);

	messenger_.Subscribe(TypeidSystem::GetTypeID<StartMoveSemMsg>(), transformComponent_);

	messenger_.Subscribe(TypeidSystem::GetTypeID<StopJumpSemMsg>(), physicsComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartJumpSemMsg>(), physicsComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartMoveSemMsg>(), physicsComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartIdleSemMsg>(), physicsComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartKnockBackSemMsg>(), physicsComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartAttackSemMsg>(), physicsComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartDashSemMsg>(), physicsComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<EndDashSemMsg>(), physicsComponent_);

	messenger_.Subscribe(TypeidSystem::GetTypeID<EndKnockBackSemMsg>(), combatStatusComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartDashSemMsg>(), combatStatusComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<EndDashSemMsg>(), combatStatusComponent_);

	messenger_.Subscribe(TypeidSystem::GetTypeID<StartMoveSemMsg>(), animationComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartIdleSemMsg>(), animationComponent_);

	messenger_.Subscribe(TypeidSystem::GetTypeID<StartJumpSemMsg>(), soundComponent_);
	messenger_.Subscribe(TypeidSystem::GetTypeID<StartKnockBackSemMsg>(), soundComponent_);
}

void Player::Update()
{
	GameObject::Update();
}

void Player::Render()
{
	GameObject::Render();
}

void Player::Term()
{
	GameObject::Term();
}

Direction Player::GetDirection() const
{
	if (!transformComponent_)
		return Direction::NONE;
	return transformComponent_->GetDirection();
}

Lib::Math::Vector2f Player::GetVelocity() const
{
	if (!physicsComponent_)
		return { 0.0f,0.0f };
	return physicsComponent_->GetVelocity();
}

float Player::GetVelocityX() const
{
	return GetVelocity().x;
}

float Player::GetVelocityY() const
{
	return GetVelocity().y;
}

Lib::Math::Vector2f Player::GetPosition() const
{
	if (!transformComponent_)
		return { 0.0f,0.0f };
	return transformComponent_->GetPosition();
}

float Player::GetPositionX() const
{
	return GetPosition().x;
}

float Player::GetPositionY() const
{
	return GetPosition().y;
}

bool Player::IsAlive() const
{
	return !IsDead();
}

bool Player::IsDead() const
{
	if (stateComponent_)
		return healthComponent_->IsDead();
	return false;
}

bool Player::IsReachedGoal() const
{
	// TODO:for now
	return false;
}

int Player::GetHp() const
{
	if (healthComponent_)
		return healthComponent_->GetHp();
	return -1;
}

bool Player::Grounded() const
{
	if (groundSensorComponent_)
		return groundSensorComponent_->Detected();
	return false;
}

int Player::IsInVincible() const
{
	if (!combatStatusComponent_)
		return -1;
	return combatStatusComponent_->IsInvincible();
}

bool Player::IsAttacking() const
{
	if (!equipmentComponent_)
		return false;
	return equipmentComponent_->IsAttacking();
}

bool Player::IsStageCleared() const
{
	if (!stateComponent_)
		return false;

	PlayerStateComponent* playerStateComponent = dynamic_cast<PlayerStateComponent*>(stateComponent_);
	if (playerStateComponent)
		return playerStateComponent->IsStageCleared();
	return false;
}

void Player::ResetState()
{
	if (stateComponent_)
	{
		delete stateComponent_;
		stateComponent_ = nullptr;
	}

	stateComponent_ = new PlayerStateComponent(true,&messenger_,this);
}

int Player::GetRemainingInvincibleFrames() const
{
	if (!combatStatusComponent_)
		return -1;
	return combatStatusComponent_->GetRemainingInvincibilityFrames();
}

void Player::ResetPlayer()
{
	IStateComponent* statementComponent = GetComponent<IStateComponent>();

	if (statementComponent)
	{
		messenger_.Unsubscribe(stateComponent_);
		IStateComponent* newComp = new PlayerStateComponent(true, &messenger_, this);
		stateComponent_ = newComp;
		SetComponent<IStateComponent>(stateComponent_);
		StateComponentSubscribeMsg();
		stateComponent_->Init();
	}
}

float Player::GetNormalizedHp() const
{
	if (healthComponent_)
		return  healthComponent_->GetNormalizedHp();
	return 0.0f;
}
