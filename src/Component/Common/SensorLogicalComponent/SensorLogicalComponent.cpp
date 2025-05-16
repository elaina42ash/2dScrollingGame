#include "Component/Common/SensorLogicalComponent/Class/SensorLogicalComponent.h"
SensorLogicalComponent::SensorLogicalComponent(bool _isActive, IMessenger* _messenger) : Component(_isActive, _messenger)

{
}

SensorLogicalComponent::SensorLogicalComponent(IMessenger* _messenger) : Component(_messenger)
{
}

void SensorLogicalComponent::Init()
{
	Component::Init();
}

void SensorLogicalComponent::Update()
{

	Component::Update();
}

void SensorLogicalComponent::Render()
{
	Component::Render();
}

void SensorLogicalComponent::Term()
{
	Component::Term();
}

void SensorLogicalComponent::Reset()
{
	Component::Reset();
}
