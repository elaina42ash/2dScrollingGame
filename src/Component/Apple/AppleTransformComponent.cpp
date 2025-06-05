#include "Component/Apple/AppleTransformComponent.h"

AppleTransformComponent::AppleTransformComponent(bool _isActive, IMessenger* _messenger) : TransformComponent(_isActive, _messenger)
{
}

AppleTransformComponent::AppleTransformComponent(IMessenger* _messenger) : TransformComponent(_messenger)
{
}

void AppleTransformComponent::Init()
{
	TransformComponent::Init();
}

void AppleTransformComponent::Update()
{
	TransformComponent::Update();

	Reset();
}

void AppleTransformComponent::Render()
{
	TransformComponent::Render();
}

void AppleTransformComponent::Term()
{
	TransformComponent::Term();
}

void AppleTransformComponent::HandleMessage(const IEventMessage& _msg)
{

}

void AppleTransformComponent::Reset()
{
	TransformComponent::Reset();
}
