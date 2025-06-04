#include "Component/Goal/GoalAnimationComponent.h"

GoalAnimationComponent::GoalAnimationComponent(bool _isActive, IMessenger* _messenger, IStaticObjectView* _staticObjectView) : AnimationComponent(_isActive, _messenger), staticObjectView_(_staticObjectView)
{

}

GoalAnimationComponent::GoalAnimationComponent(IMessenger* _messenger, IStaticObjectView* _staticObjectView) : AnimationComponent(_messenger), staticObjectView_(_staticObjectView)
{

}

void GoalAnimationComponent::Init()
{
	AnimationComponent::Init();

	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (staticObjectView_)
		_newPos = staticObjectView_->GetPosition();

	InitTexture("Images/2dAction/goal.png");

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

void GoalAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (staticObjectView_)
		_newPos = staticObjectView_->GetPosition();

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	AnimationComponent::Update();

	Reset();
}

void GoalAnimationComponent::Render()
{
	AnimationComponent::Render();
}

void GoalAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void GoalAnimationComponent::HandleMessage(const IEventMessage& _msg)
{

}

void GoalAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}
