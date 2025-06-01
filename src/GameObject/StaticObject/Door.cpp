#include "GameObject/StaticObject/Door.h"
#include "Component/Door/DoorAnimationComponent.h"
#include "Component/Door/DoorCollisionComponent.h"
#include "Component/Door/DoorTransformComponent.h"
#include "Component/IronSpike/IronSpikeAnimationComponent.h"
#include "Component/IronSpike/IronSpikeCollisionComponent.h"
#include "Component/IronSpike/IronSpikeTransformComponent.h"

Door::Door()
{
	transformComponent_ = new DoorTransformComponent(true, AccessMessenger());
	AddComponent<ITransformComponent>(transformComponent_);
	collisionComponent_ = new DoorCollisionComponent(true, AccessMessenger(), this);
	AddComponent<ICollisionComponent>(collisionComponent_);
	animationComponent_ = new DoorAnimationComponent(true, AccessMessenger(), this);
	AddComponent<IAnimationComponent>(animationComponent_);
}

Door::~Door()
{
	if (collisionComponent_)
	{
		delete collisionComponent_;
		collisionComponent_ = nullptr;
	}
	if (transformComponent_)
	{
		delete transformComponent_;
		transformComponent_ = nullptr;
	}
	if (animationComponent_)
	{
		delete animationComponent_;
		animationComponent_ = nullptr;
	}
}

void Door::Init()
{
	StaticObject::Init();

}

void Door::Update()
{
	StaticObject::Update();

}

void Door::Render()
{
	StaticObject::Render();

}

void Door::Term()
{
	StaticObject::Term();
}

void Door::HandleMessage(const IEventMessage& _msg)
{

}

Lib::Math::Vector2f Door::GetPosition() const
{
	if (!transformComponent_)
		return { 0.0f,0.0f };
	return transformComponent_->GetPosition();
}
