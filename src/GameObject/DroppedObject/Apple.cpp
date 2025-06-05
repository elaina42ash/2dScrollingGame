#include "GameObject/DroppedObject/Apple.h"

#include "Component/Apple/AppleAnimationComponent.h"
#include "Component/Apple/AppleCollisionComponent.h"
#include "Component/Apple/AppleMovementComponent.h"
#include "Component/Apple/ApplePhysicsComponent.h"
#include "Component/Apple/AppleTileMapSensorComponent.h"
#include "Component/Apple/AppleTransformComponent.h"

Apple::Apple()
{
	transformComponent_ = new AppleTransformComponent(true, AccessMessenger());
	animationComponent_ = new AppleAnimationComponent(true, AccessMessenger(), this);
	collisionComponent_ = new AppleCollisionComponent(true, AccessMessenger(), this);
	physicsComponent_ = new ApplePhysicsComponent(true, AccessMessenger(), this);
	movementComponent_ = new AppleMovementComponent(true, AccessMessenger(), this);
	tileMapSensorComponent_ = new AppleTileMapSensorComponent(true, AccessMessenger(), this);

	AddComponent<ITransformComponent>(transformComponent_);
	AddComponent<IAnimationComponent>(animationComponent_);
	AddComponent<ICollisionComponent>(collisionComponent_);
	AddComponent<IPhysicsComponent>(physicsComponent_);
	AddComponent<IMovementComponent>(movementComponent_);
	AddComponent<ITileMapSensorComponent>(tileMapSensorComponent_);
}

Apple::~Apple()
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

void Apple::Init()
{
	DroppedObject::Init();

	SetComponentPriority<ITransformComponent>(0);
	SetComponentPriority<ITileMapSensorComponent>(1);
	SetComponentPriority<ICollisionComponent>(2);
	SetComponentPriority<IAnimationComponent>(3);
	SetComponentPriority<IPhysicsComponent>(4);
	SetComponentPriority<IMovementComponent>(5);
}

void Apple::Update()
{
	DroppedObject::Update();
}

void Apple::Render()
{
	DroppedObject::Render();
}

void Apple::Term()
{
	DroppedObject::Term();
}

void Apple::HandleMessage(const IEventMessage& _msg)
{

}


