#include "Component/Goal/GoalTransformComponent.h"

GoalTransformComponent::GoalTransformComponent(bool _isActive, IMessenger* _messenger) : TransformComponent(_isActive, _messenger)
{
}

GoalTransformComponent::GoalTransformComponent(IMessenger* _messenger) : TransformComponent(_messenger)
{
}

void GoalTransformComponent::Init()
{
	TransformComponent::Init();
}

void GoalTransformComponent::Update()
{
	TransformComponent::Update();

	Reset();
}

void GoalTransformComponent::Render()
{
	TransformComponent::Render();
}

void GoalTransformComponent::Term()
{
	TransformComponent::Term();
}

void GoalTransformComponent::HandleMessage(const IEventMessage& _msg)
{

}

void GoalTransformComponent::Reset()
{
	TransformComponent::Reset();
}
