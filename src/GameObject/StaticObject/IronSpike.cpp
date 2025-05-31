#include "GameObject/StaticObject/IronSpike.h"
#include "Component/IronSpike/IronSpikeAnimationComponent.h"
#include "Component/IronSpike/IronSpikeCollisionComponent.h"
#include "Component/IronSpike/IronSpikeTransformComponent.h"

IronSpike::IronSpike()
{
	transformComponent_ = new IronSpikeTransformComponent(true, AccessMessenger());
	AddComponent<ITransformComponent>(transformComponent_);
	collisionComponent_ = new IronSpikeCollisionComponent(true, AccessMessenger(),this);
	AddComponent<ICollisionComponent>(collisionComponent_);
	animationComponent_ = new IronSpikeAnimationComponent(true, AccessMessenger(),this);
	AddComponent<IAnimationComponent>(animationComponent_);
}

IronSpike::~IronSpike()
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

Lib::Math::Vector2f IronSpike::GetPosition() const
{
	if (!transformComponent_)
		return { 0.0f,0.0f };
	return transformComponent_->GetPosition();
}
