#include "Component/IronSpike/IronSpikeAnimationComponent.h"

IronSpikeAnimationComponent::IronSpikeAnimationComponent(bool _isActive, IMessenger* _messenger, IStaticObjectView* _staticObjectView): AnimationComponent(_isActive, _messenger)
{
}

IronSpikeAnimationComponent::IronSpikeAnimationComponent(IMessenger* _messenger): AnimationComponent(_messenger)
{
}

void IronSpikeAnimationComponent::Init()
{
	AnimationComponent::Init();

	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };

	if (staticObjectView_)
		_newPos = staticObjectView_->GetPosition();

	InitTexture("Images/2dAction/Goal.png");

	SpriteParams params = {
		_newPos,
		128.0f,64.0f,
		true,
		0.0f
	};

	InitSprite(params, texture_);
}

void IronSpikeAnimationComponent::Update()
{
	AnimationComponent::Update();
}

void IronSpikeAnimationComponent::Render()
{
	AnimationComponent::Render();
}

void IronSpikeAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void IronSpikeAnimationComponent::HandleMessage(const IEventMessage& _msg)
{
		
}

void IronSpikeAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}
