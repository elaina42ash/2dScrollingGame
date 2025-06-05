#include "GameObject/DroppedObject/DroppedKatana.h"

#include "Component/DroppedKatana/DroppedKatanaAnimationComponent.h"
#include "Component/DroppedKatana/DroppedKatanaCollisionComponent.h"
#include "Component/DroppedKatana/DroppedKatanaMovementComponent.h"
#include "Component/DroppedKatana/DroppedKatanaPhysicsComponent.h"
#include "Component/DroppedKatana/DroppedKatanaTileMapSensorComponent.h"
#include "Component/DroppedKatana/DroppedKatanaTransformComponent.h"

DroppedKatana::DroppedKatana() : Katana_(std::make_shared<Katana>())
{
	transformComponent_ = new DroppedKatanaTransformComponent(true, AccessMessenger());
	animationComponent_ = new DroppedKatanaAnimationComponent(true, AccessMessenger(), this);
	collisionComponent_ = new DroppedKatanaCollisionComponent(true, AccessMessenger(), this);
	physicsComponent_ = new DroppedKatanaPhysicsComponent(true, AccessMessenger(), this);
	movementComponent_ = new DroppedKatanaMovementComponent(true, AccessMessenger(), this);
	tileMapSensorComponent_ = new DroppedKatanaTileMapSensorComponent(true, AccessMessenger(), this);

	AddComponent<ITransformComponent>(transformComponent_);
	AddComponent<IAnimationComponent>(animationComponent_);
	AddComponent<ICollisionComponent>(collisionComponent_);
	AddComponent<IPhysicsComponent>(physicsComponent_);
	AddComponent<IMovementComponent>(movementComponent_);
	AddComponent<ITileMapSensorComponent>(tileMapSensorComponent_);
}

DroppedKatana::~DroppedKatana()
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

std::shared_ptr<Katana> DroppedKatana::GetKatana() const
{
	return Katana_;
}


void DroppedKatana::Init()
{
	DroppedObject::Init();

	SetComponentPriority<ITransformComponent>(0);
	SetComponentPriority<ITileMapSensorComponent>(1);
	SetComponentPriority<ICollisionComponent>(2);
	SetComponentPriority<IAnimationComponent>(3);
	SetComponentPriority<IPhysicsComponent>(4);
	SetComponentPriority<IMovementComponent>(5);
}

void DroppedKatana::Update()
{
	DroppedObject::Update();
}

void DroppedKatana::Render()
{
	DroppedObject::Render();
}

void DroppedKatana::Term()
{
	DroppedObject::Term();
}

void DroppedKatana::HandleMessage(const IEventMessage& _msg)
{

}


