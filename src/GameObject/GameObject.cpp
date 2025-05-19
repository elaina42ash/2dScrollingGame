#include "GameObject/GameObject.h"

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

bool GameObject::IsActive() const
{
	return isActive_;
}

void GameObject::Enable()
{
	SetActive(true);
}

void GameObject::Disable()
{
	SetActive(false);
}

void GameObject::SetTag(const char* _tag)
{
	if (!_tag)
	{
		tag_ = "";
		return;
	}

	tag_ = _tag;
}

const char* GameObject::GetTag() const
{
	if (!tag_)
		return "";

	return tag_;
}

bool GameObject::IsMarkedToDestroy() const
{
	return isDestroyed_;
}

void GameObject::MarkToDestroy()
{
	isDestroyed_ = true;
}

void GameObject::SetActive(bool _isActive)
{
	isActive_ = _isActive;
}

void GameObject::SendMsg(const IEventMessage& _msg)
{
	messenger_.SendMsg(_msg);
}

void GameObject::Subscribe(size_t _msgType, IMessageListener* _listener)
{
	messenger_.Subscribe(_msgType, _listener);
}

void GameObject::Unsubscribe(size_t _msgType, IMessageListener* _listener)
{
	messenger_.Unsubscribe(_msgType, _listener);
}

void GameObject::Unsubscribe(IMessageListener* _listener)
{
	messenger_.Unsubscribe(_listener);
}

Messenger* GameObject::AccessMessenger()
{
	return &messenger_;
}

void GameObject::ApplyActiveChanges()
{
	for (auto* comp : sortedComponents_) {
		if (auto* c = dynamic_cast<Component*>(comp)) {
			c->ApplyActiveChange();
		}
	}
}


