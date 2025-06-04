#include "GameObject/DroppedObject/DroppedSword.h"

#include "Component/DroppedSword/DroppedSwordAnimationComponent.h"
#include "Component/DroppedSword/DroppedSwordCollisionComponent.h"
#include "Component/DroppedSword/DroppedSwordMovementComponent.h"
#include "Component/DroppedSword/DroppedSwordPhysicsComponent.h"
#include "Component/DroppedSword/DroppedSwordTileMapSensorComponent.h"
#include "Component/DroppedSword/DroppedSwordTransformComponent.h"

DroppedSword::DroppedSword(): sword_(std::make_shared<Sword>())
{
	transformComponent_ = new DroppedSwordTransformComponent(true,AccessMessenger());
	animationComponent_ = new DroppedSwordAnimationComponent(true, AccessMessenger(), this);
	collisionComponent_ = new DroppedSwordCollisionComponent(true,AccessMessenger(),this);
	physicsComponent_ = new DroppedSwordPhysicsComponent(true,AccessMessenger(),this);
	movementComponent_ = new DroppedSwordMovementComponent(true,AccessMessenger(),this);
	tileMapSensorComponent_ = new DroppedSwordTileMapSensorComponent(true,AccessMessenger(),this);

	AddComponent<ITransformComponent>(transformComponent_);
	AddComponent<IAnimationComponent>(animationComponent_);
	AddComponent<ICollisionComponent>(collisionComponent_);
	AddComponent<IPhysicsComponent>(physicsComponent_);
	AddComponent<IMovementComponent>(movementComponent_);
	AddComponent<ITileMapSensorComponent>(tileMapSensorComponent_);
}

DroppedSword::~DroppedSword()
{
	if (transformComponent_)
	{
		delete transformComponent_;
		transformComponent_ = nullptr;
	}

	if (tileMapSensorComponent_)
	{
		delete tileMapSensorComponent_;
		tileMapSensorComponent_ = nullptr;
	}

	if (animationComponent_)
	{
		delete animationComponent_;
		animationComponent_ = nullptr;
	}

	if (collisionComponent_)
	{
		delete collisionComponent_;
		collisionComponent_ = nullptr;
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
}



void DroppedSword::Init()
{
	DroppedObject::Init();

	SetComponentPriority<ITransformComponent>(0);
	SetComponentPriority<ITileMapSensorComponent>(1);
	SetComponentPriority<ICollisionComponent>(2);
	SetComponentPriority<IAnimationComponent>(3);
	SetComponentPriority<IPhysicsComponent>(4);
	SetComponentPriority<IMovementComponent>(5);
}

void DroppedSword::Update()
{
	DroppedObject::Update();
}

void DroppedSword::Render()
{
	DroppedObject::Render();
}

void DroppedSword::Term()
{
	DroppedObject::Term();
}

void DroppedSword::HandleMessage(const IEventMessage& _msg)
{
		
}

