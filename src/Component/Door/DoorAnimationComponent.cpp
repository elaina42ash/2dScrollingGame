#include "Component/Door/DoorAnimationComponent.h"

DoorAnimationComponent::DoorAnimationComponent(bool _isActive, IMessenger* _messenger, IStaticObjectView* _staticObjectView) : AnimationComponent(_isActive, _messenger), staticObjectView_(_staticObjectView)
{

}

DoorAnimationComponent::DoorAnimationComponent(IMessenger* _messenger, IStaticObjectView* _staticObjectView) : AnimationComponent(_messenger), staticObjectView_(_staticObjectView)
{

}

void DoorAnimationComponent::Init()
{
	AnimationComponent::Init();

	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (staticObjectView_)
		_newPos = staticObjectView_->GetPosition();

	InitTexture("Images/2dAction/door.png");

	SpriteParams params = {
		_newPos,
		32.0f,64.0f,
		true,
		0.0f
	};


	InitSprite(params, texture_);

	sprite_.SetPivot(Pivot::TopLeft);

	DrawSprite();
}

void DoorAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (staticObjectView_)
		_newPos = staticObjectView_->GetPosition();

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	AnimationComponent::Update();

	Reset();
}

void DoorAnimationComponent::Render()
{
	AnimationComponent::Render();
}

void DoorAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void DoorAnimationComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DoorAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}
