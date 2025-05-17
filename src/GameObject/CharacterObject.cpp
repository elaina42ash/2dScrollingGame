#include "GameObject/CharacterObject.h"

#include "Component/Common/Component.h"

void CharacterObject::Init()
{
	GameObject::Init();
}

void CharacterObject::Update()
{
	GameObject::Update();
}

void CharacterObject::Render()
{
	GameObject::Render();
}

void CharacterObject::Term()
{
	GameObject::Term();
}

void CharacterObject::InjectEnvironment(IEnvironmentQuery* _environmentQuery)
{
	environmentQuery_.Bind(_environmentQuery);
}