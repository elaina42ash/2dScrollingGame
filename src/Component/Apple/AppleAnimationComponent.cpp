#include "Component/Apple/AppleAnimationComponent.h"


AppleAnimationComponent::AppleAnimationComponent(bool _isActive, IMessenger* messenger_,
	IDroppedObjectView* _droppedObjectView) : AnimationComponent(_isActive, messenger_),
	droppedObjectView_(_droppedObjectView)
{
}

AppleAnimationComponent::AppleAnimationComponent(IMessenger* messenger_,
	IDroppedObjectView* _droppedObjectView) : AnimationComponent(messenger_),
	droppedObjectView_(_droppedObjectView)
{
}

void AppleAnimationComponent::Init()
{
	AnimationComponent::Init();

	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (droppedObjectView_)
		_newPos = droppedObjectView_->GetPosition();

	InitTexture("Images/2dAction/Apple.png");

	SpriteParams params = {
		_newPos,
		32.0f,32.0f,
		true,
		0.0f
	};


	InitSprite(params, texture_);

	sprite_.SetPivot(Pivot::TopLeft);

	DrawSprite();
}

void AppleAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (droppedObjectView_)
		_newPos = { droppedObjectView_->GetPosition().x - 16.0f,droppedObjectView_->GetPosition().y + 16.0f };

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	AnimationComponent::Update();

	Reset();
}

void AppleAnimationComponent::Render()
{
	AnimationComponent::Render();
}

void AppleAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void AppleAnimationComponent::HandleMessage(const IEventMessage& _msg)
{

}

void AppleAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}
