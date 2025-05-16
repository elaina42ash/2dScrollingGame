#include "GameObject/GameObject.h"

#include <algorithm>

#include "Component/Common/Component.h"

GameObject::GameObject():messenger_(&messageBus_)
{
		
}

void GameObject::Init()
{
	for (auto* comp : sortedComponents_)
	{
		if (comp)
			comp->Init();
	}
		
}

void GameObject::Update()
{
	ApplyActiveChanges();

	for (auto* comp : sortedComponents_)
	{
		if (comp && comp->IsActive())
			comp->Update();
	}
		
}

void GameObject::Render()
{
	for (auto* comp : sortedComponents_)
	{
		if (comp && comp->IsActive())
			comp->Render();
	}
	
}

void GameObject::Term()
{
	for (auto* comp : sortedComponents_)
	{
		if (comp)
			comp->Term();
	}
		
	components_.clear();
}

void GameObject::ApplyActiveChanges()
{
	for (auto* comp : sortedComponents_) {
		if (auto* c = dynamic_cast<Component*>(comp)) {
			c->ApplyActiveChange();
		}
	}
}

