#include "Component/DroppedSword/DroppedSwordAnimationComponent.h"


DroppedSwordAnimationComponent::DroppedSwordAnimationComponent(bool _isActive, IMessenger* messenger_,
	IDroppedObjectView* _droppedObjectView): AnimationComponent(_isActive, messenger_),
	                                         droppedObjectView_(_droppedObjectView)
{
}

DroppedSwordAnimationComponent::DroppedSwordAnimationComponent(IMessenger* messenger_,
	IDroppedObjectView* _droppedObjectView): AnimationComponent(messenger_),
	                                         droppedObjectView_(_droppedObjectView)
{
}

void DroppedSwordAnimationComponent::Init()
{
	AnimationComponent::Init();

	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (droppedObjectView_)
		_newPos = droppedObjectView_->GetPosition();

	InitTexture("Images/2dAction/sword.png");

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

void DroppedSwordAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (droppedObjectView_)
		_newPos = droppedObjectView_->GetPosition();

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	AnimationComponent::Update();

	Reset();
}

void DroppedSwordAnimationComponent::Render()
{
	AnimationComponent::Render();
}

void DroppedSwordAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void DroppedSwordAnimationComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DroppedSwordAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}
