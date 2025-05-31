#include "GameObject/StaticObject/IronSpike.h"
#include "Component/IronSpike/IronSpikeAnimationComponent.h"
#include "Component/IronSpike/IronSpikeCollisionComponent.h"
#include "Component/IronSpike/IronSpikeTransformComponent.h"

IronSpike::IronSpike()
{
	transformComponent_ = new IronSpikeTransformComponent(false, AccessMessenger());
	AddComponent<ITransformComponent>(transformComponent_);
	collisionComponent_ = new IronSpikeCollisionComponent(false, AccessMessenger());
	AddComponent<ICollisionComponent>(collisionComponent_);
	animationComponent_ = new IronSpikeAnimationComponent(false, AccessMessenger(),this);
	AddComponent<IAnimationComponent>(animationComponent_);
}

IronSpike::~IronSpike()
{
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
}

void IronSpike::Init()
{
	StaticObject::Init();

}

void IronSpike::Update()
{
	StaticObject::Update();
}

void IronSpike::Render()
{
	StaticObject::Render();
}

void IronSpike::Term()
{
	StaticObject::Term();
}

void IronSpike::HandleMessage(const IEventMessage& _msg)
{
		
}
