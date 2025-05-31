#include "Component/IronSpike/IronSpikeTransformComponent.h"

IronSpikeTransformComponent::IronSpikeTransformComponent(bool _isActive, IMessenger* _messenger): TransformComponent(_isActive, _messenger)
{
}

IronSpikeTransformComponent::IronSpikeTransformComponent(IMessenger* _messenger): TransformComponent(_messenger)
{
}

void IronSpikeTransformComponent::Init()
{
	TransformComponent::Init();
}

void IronSpikeTransformComponent::Update()
{
	TransformComponent::Update();

	Reset();
}

void IronSpikeTransformComponent::Render()
{
	TransformComponent::Render();
}

void IronSpikeTransformComponent::Term()
{
	TransformComponent::Term();
}

void IronSpikeTransformComponent::HandleMessage(const IEventMessage& _msg)
{
		
}

void IronSpikeTransformComponent::Reset()
{
	TransformComponent::Reset();
}
