#include "Component/Common/ExecutorComponent/Class/MovementComponent.h"

MovementComponent::MovementComponent(bool _isActive,IMessenger* _messenger) : ExecutorComponent(_isActive, _messenger)
{

}

MovementComponent::MovementComponent(IMessenger* _messenger) : ExecutorComponent(_messenger)
{

}

void MovementComponent::Init()
{
	ExecutorComponent::Init();
	transformComponent_.Bind(GetComponent<ITransformComponent>());
	tileMapSensorComponent_.Bind(GetComponent<ITileMapSensorComponent>());
	collisionComponent_.Bind(GetComponent<ICollisionComponent>());
	physicsComponent_.Bind(GetComponent<IPhysicsComponent>());
}

void MovementComponent::Update()
{
	ExecutorComponent::Update();
}

void MovementComponent::Render()
{
	ExecutorComponent::Render();
}

void MovementComponent::Term()
{
	ExecutorComponent::Term();
}

void MovementComponent::Reset()
{
	ExecutorComponent::Reset();
}
