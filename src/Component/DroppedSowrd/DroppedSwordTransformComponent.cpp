#include "Component/DroppedSword/DroppedSwordTransformComponent.h"

DroppedSwordTransformComponent::DroppedSwordTransformComponent(bool _isActive, IMessenger* _messenger): TransformComponent(_isActive, _messenger)
{
}

DroppedSwordTransformComponent::DroppedSwordTransformComponent(IMessenger* _messenger): TransformComponent(_messenger)
{
}

void DroppedSwordTransformComponent::Init()
{
	TransformComponent::Init();
}

void DroppedSwordTransformComponent::Update()
{
	TransformComponent::Update();

	Reset();
}

void DroppedSwordTransformComponent::Render()
{
	TransformComponent::Render();
}

void DroppedSwordTransformComponent::Term()
{
	TransformComponent::Term();
}

void DroppedSwordTransformComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DroppedSwordTransformComponent::Reset()
{
	TransformComponent::Reset();
}
