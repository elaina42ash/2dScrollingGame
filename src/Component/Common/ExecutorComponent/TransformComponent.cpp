#include "Component/Common/ExecutorComponent/Class/TransformComponent.h"

TransformComponent::TransformComponent(bool _isActive, IMessenger* _messenger) : ExecutorComponent(_isActive, _messenger)
{
}

TransformComponent::TransformComponent(IMessenger* _messenger) :ExecutorComponent(_messenger)
{

}

void TransformComponent::SetPosition(const Lib::Math::Vector2f& _new)
{
	position_ = _new;
}

void TransformComponent::SetDirection(const Direction& _new)
{
	direction_ = _new;
}


void TransformComponent::Init()
{
	ExecutorComponent::Init();
}

void TransformComponent::Update()
{
	ExecutorComponent::Update();
}

void TransformComponent::Render()
{
	ExecutorComponent::Render();
}

void TransformComponent::Term()
{
	ExecutorComponent::Term();
}

void TransformComponent::Reset()
{
	ExecutorComponent::Reset();
}



Direction TransformComponent::GetDirection() const
{
	return direction_;
}

void TransformComponent::ChangeDirection(const Direction& _new)
{
	SetDirection(_new);
}

void TransformComponent::ReverseDirection()
{
	if (direction_ == Direction::RIGHT)
		direction_ = Direction::LEFT;
	else if (direction_ == Direction::LEFT)
		direction_ = Direction::RIGHT;
}

const Lib::Math::Vector2f& TransformComponent::GetPosition() const
{
	return position_;
}

float TransformComponent::GetPositionY() const
{
	return GetPosition().y;
}

float TransformComponent::GetPositionX() const
{
	return GetPosition().x;
}

void TransformComponent::Translate(const Lib::Math::Vector2f& _offset)
{
	SetPosition(GetPosition() + _offset);
}

void TransformComponent::MoveTo(const Lib::Math::Vector2f& _target)
{
	SetPosition(_target);
}
