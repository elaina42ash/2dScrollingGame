#include "Component/Common/Component.h"
#include "Fwk/Framework.h"
#include "GameObject/GameObject.h"

Component::Component(bool _isActive, IMessenger* _messenger) : isActive_(_isActive),messenger_(_messenger)
{
}


void Component::SetActive(bool _isActive)
{
	nextActive = _isActive;
}

void Component::ApplyActiveChange()
{
	isActive_ = nextActive;
}

Component::Component(IMessenger* _messenger):messenger_(_messenger)
{
		
}

void Component::Enable()
{
	SetActive(true);
}

void Component::Disable()
{
	SetActive(false);
}

GameObject* Component::GetOwner() const
{
	return owner_;
}

void Component::SetOwner(GameObject* _owner)
{
	owner_ = _owner;
}

void Component::Init()
{
	timer_.Reset();
}

void Component::Update()
{
	timer_.Update(Time_I->GetDeltaTime());
}

void Component::Render()
{

}

void Component::Term()
{

}

int Component::GetPriority() const
{
	return priority_;
}

void Component::SetPriority(const int _priority)
{
	priority_ = _priority;
}

bool Component::IsActive() const
{
	return isActive_;
}

void Component::Reset()
{

}

void Component::SendMsg(const IEventMessage& _message)
{
	if (!messenger_)
		return;
	messenger_->SendMsg(_message);
}

IMessenger* Component::GetMessengerPtr()
{
	return messenger_.Injected();
}
