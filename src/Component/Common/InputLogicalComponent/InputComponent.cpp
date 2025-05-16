#include "Component/Common/InputLogicalComponent/Class/InputComponent.h"

void InputComponent::Init()
{
	InputLogicalComponent::Init();
}

void InputComponent::Update()
{
	InputLogicalComponent::Update();
}

void InputComponent::Render()
{
	InputLogicalComponent::Render();
}

void InputComponent::Term()
{
	InputLogicalComponent::Term();
}

void InputComponent::Reset()
{
	InputLogicalComponent::Reset();
}

InputComponent::InputComponent(bool _isActive, IMessenger* _messenger) : InputLogicalComponent(_isActive, _messenger),logicalInputAdapter_(&physicsInputAdapter_, &inputMapper_)
{
}

InputComponent::InputComponent(IMessenger* _messenger) : InputLogicalComponent(_messenger), logicalInputAdapter_(&physicsInputAdapter_, &inputMapper_)
{
}


