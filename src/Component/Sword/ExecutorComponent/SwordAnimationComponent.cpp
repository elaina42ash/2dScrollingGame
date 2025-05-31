#include "Component/Sword/ExecutorComponent/Class/SwordAnimationComponent.h"

#include "Animation/AnimationDef.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"
#include "Fwk/Framework.h"

SwordAnimationComponent::SwordAnimationComponent(bool _isActive, IMessenger* messenger_, IWeaponView* _swordView) : AnimationComponent(_isActive, messenger_),
swordView_(_swordView)
{
}

SwordAnimationComponent::SwordAnimationComponent(IMessenger* messenger_, IWeaponView* _swordView) : AnimationComponent(messenger_),
swordView_(_swordView)
{
}

void SwordAnimationComponent::Init()
{
	AnimationComponent::Init();

	ITransformComponent* transformComponent = GetComponent<ITransformComponent>();

	Vector2f pos = { 0.0f,0.0f };
	if (transformComponent)
		pos = transformComponent->GetPosition();

	InitTexture("Images/2dAction/sword.png");

	SpriteParams params = {
	pos,
	128.0f,64.0f,
	false,
	0.0f
	};

	InitSprite(params, texture_);

	RegisterSwordAnimation();
}

void SwordAnimationComponent::HandleSwordSwingAnimation()
{
	AnimationRequest animationRequest = {
		static_cast<int>(SwordAnimationType::NONE),
		AnimationPlayStyle::Default,
		10,
		true,
	};

	switch (swordView_->GetDirection())
	{
	case Direction::RIGHT:animationRequest.animationID = static_cast<int>(SwordAnimationType::SWING_RIGHT);
		break;
	case Direction::LEFT:animationRequest.animationID = static_cast<int>(SwordAnimationType::SWING_LEFT);
		break;
	default:
		break;
	}

	AddAnimationTask(animationRequest);
}

void SwordAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };
	if (swordView_)
		_newPos = swordView_->GetPosition();

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	AnimationComponent::Update();

	// スプライトの更新
	UpdateSprite();

	Reset();
}

void SwordAnimationComponent::Render()
{
	AnimationComponent::Render();

	DrawSprite();
}

void SwordAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void SwordAnimationComponent::HandleMessage(const IEventMessage& _msg)
{

}

void SwordAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}

void SwordAnimationComponent::OnAnimationEvent(const AnimationEvent& _animEvent)
{
}

void SwordAnimationComponent::RegisterSwordAnimation()
{

}
