#include "Component/Common/DecisionLogicalComponent/Class/DecisionLogicalComponent.h"
#include "Component/Common/Component.h"

DecisionLogicalComponent::DecisionLogicalComponent(bool _isActive, IMessenger* _messenger) : Component(_isActive, _messenger){

}

DecisionLogicalComponent::DecisionLogicalComponent(IMessenger* _messenger) : Component(_messenger)
{
}

void DecisionLogicalComponent::Init()
{
	Component::Init();
}

void DecisionLogicalComponent::Update()
{
	Component::Update();
}

void DecisionLogicalComponent::Render()
{
	Component::Render();
}

void DecisionLogicalComponent::Term()
{
	Component::Term();
}

void DecisionLogicalComponent::Reset()
{
	Component::Reset();
}
