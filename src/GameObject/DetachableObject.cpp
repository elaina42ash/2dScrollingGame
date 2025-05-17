#include "GameObject/DetachableObject.h"

void DetachableObject::Init()
{
	GameObject::Init();
}

void DetachableObject::Update()
{
	GameObject::Update();
}

void DetachableObject::Render()
{
	GameObject::Render();
}

void DetachableObject::Term()
{
	GameObject::Term();
}

DetachableObjectState DetachableObject::GetState() const
{
	return objectState_;
}

void DetachableObject::SetOwner(CharacterObject* _owner)
{
	owner_.Bind(_owner);
}

DetachableObject::DetachableObject(DetachableObjectState _objectState): objectState_(_objectState)
{
}
