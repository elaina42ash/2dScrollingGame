#include "Component/DroppedKatana/DroppedKatanaTransformComponent.h"

DroppedKatanaTransformComponent::DroppedKatanaTransformComponent(bool _isActive, IMessenger* _messenger) : TransformComponent(_isActive, _messenger)
{
}

DroppedKatanaTransformComponent::DroppedKatanaTransformComponent(IMessenger* _messenger) : TransformComponent(_messenger)
{
}

void DroppedKatanaTransformComponent::Init()
{
	TransformComponent::Init();
}

void DroppedKatanaTransformComponent::Update()
{
	TransformComponent::Update();

	Reset();
}

void DroppedKatanaTransformComponent::Render()
{
	TransformComponent::Render();
}

void DroppedKatanaTransformComponent::Term()
{
	TransformComponent::Term();
}

void DroppedKatanaTransformComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DroppedKatanaTransformComponent::Reset()
{
	TransformComponent::Reset();
}
