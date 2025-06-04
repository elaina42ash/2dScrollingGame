#include "GameObject/DroppedObject/DroppedObject.h"

void DroppedObject::Init()
{
	GameObject::Init();
}

void DroppedObject::Update()
{
	GameObject::Update();
}

void DroppedObject::Render()
{
	GameObject::Render();
}

void DroppedObject::Term()
{
	GameObject::Term();
}

Lib::Math::Vector2f DroppedObject::GetVelocity() const
{
	if (!physicsComponent_)
		return { 0.0f,0.0f };

	return physicsComponent_->GetVelocity();
}

float DroppedObject::GetVelocityX() const
{
	return GetVelocity().x;
}

float DroppedObject::GetVelocityY() const
{
	return GetVelocity().y;
}

float DroppedObject::GetPositionX() const
{
	return GetPosition().x;
}

float DroppedObject::GetPositionY() const
{
	return GetPosition().y;
}

float DroppedObject::GetTileSize() const
{
	if (!sceneContext_)
		return 0.0f;

	return sceneContext_->GetTileSize();
}

Lib::Math::Vector2f DroppedObject::GetPosition() const
{
	if (!transformComponent_)
		return { 0.0f,0.0f };

	return transformComponent_->GetPosition();
}

bool DroppedObject::IsInsideWallCircle(Lib::Math::Vector2f _position, float _radius) const
{
	if (!sceneContext_)
		return true;

	return sceneContext_->IsInsideWallCircle(_position, _radius);

}

bool DroppedObject::IsInsideWallRect(Lib::Math::Vector2f _position, float _width, float _height) const
{
	if (!sceneContext_)
		return true;

	return sceneContext_->IsInsideWallRect(_position, _width, _height);
}