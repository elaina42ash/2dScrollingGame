#include "Component/Door/DoorTransformComponent.h"

DoorTransformComponent::DoorTransformComponent(bool _isActive, IMessenger* _messenger) : TransformComponent(_isActive, _messenger)
{
}

DoorTransformComponent::DoorTransformComponent(IMessenger* _messenger) : TransformComponent(_messenger)
{
}

void DoorTransformComponent::Init()
{
	TransformComponent::Init();
}

void DoorTransformComponent::Update()
{
	TransformComponent::Update();

	Reset();
}

void DoorTransformComponent::Render()
{
	TransformComponent::Render();
}

void DoorTransformComponent::Term()
{
	TransformComponent::Term();
}

void DoorTransformComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DoorTransformComponent::Reset()
{
	TransformComponent::Reset();
}
