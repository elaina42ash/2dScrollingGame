#include "GameObject/StaticObject/Goal.h"

#include "Component/Goal/GoalAnimationComponent.h"
#include "Component/Goal/GoalCollisionComponent.h"
#include "Component/Goal/GoalTransformComponent.h"


Goal::Goal()
{
	transformComponent_ = new GoalTransformComponent(true, AccessMessenger());
	AddComponent<ITransformComponent>(transformComponent_);
	collisionComponent_ = new GoalCollisionComponent(true, AccessMessenger(), this);
	AddComponent<ICollisionComponent>(collisionComponent_);
	animationComponent_ = new GoalAnimationComponent(true, AccessMessenger(), this);
	AddComponent<IAnimationComponent>(animationComponent_);
}

Goal::~Goal()
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

void Goal::Init()
{
	StaticObject::Init();

}

void Goal::Update()
{
	StaticObject::Update();

}

void Goal::Render()
{
	StaticObject::Render();

}

void Goal::Term()
{
	StaticObject::Term();
}

void Goal::HandleMessage(const IEventMessage& _msg)
{

}

Lib::Math::Vector2f Goal::GetPosition() const
{
	if (!transformComponent_)
		return { 0.0f,0.0f };
	return transformComponent_->GetPosition();
}
