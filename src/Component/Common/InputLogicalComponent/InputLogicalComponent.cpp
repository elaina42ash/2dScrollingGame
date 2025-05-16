#include "Component/Common/InputLogicalComponent/Class/InputLogicalComponent.h"
#include "Component/Common/Component.h"
InputLogicalComponent::InputLogicalComponent(bool _isActive, IMessenger* _messenger) : Component(_isActive, _messenger)
{
}

InputLogicalComponent::InputLogicalComponent(IMessenger* _messenger) : Component(_messenger)
{
}

void InputLogicalComponent::Init()
{
	Component::Init();
}

void InputLogicalComponent::Update()
{
	Component::Update();
}

void InputLogicalComponent::Render()
{
	Component::Render();
}

void InputLogicalComponent::Term()
{
	Component::Term();
}

void InputLogicalComponent::Reset()
{
	Component::Reset();
}
