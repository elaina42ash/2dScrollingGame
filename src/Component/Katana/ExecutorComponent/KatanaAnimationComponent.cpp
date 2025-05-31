#include "Component/Katana/ExecutorComponent/KatanaAnimationComponent.h"
#include "Animation/AnimationDef.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"

KatanaAnimationComponent::KatanaAnimationComponent(bool _isActive, IMessenger* messenger_, IWeaponView* _weaponView) : AnimationComponent(_isActive, messenger_),
weaponView_(_weaponView)
{
}

KatanaAnimationComponent::KatanaAnimationComponent(IMessenger* messenger_, IWeaponView* _weaponView) : AnimationComponent(messenger_),
weaponView_(_weaponView)
{
}

void KatanaAnimationComponent::Init()
{
	AnimationComponent::Init();

}

void KatanaAnimationComponent::Update()
{
	Lib::Math::Vector2f _newPos = { 0.0f,0.0f };
	if (weaponView_)
		_newPos = weaponView_->GetPosition();

	// スプライトの位置を更新
	SetSpritePosition(_newPos);

	AnimationComponent::Update();

	Reset();
}

void KatanaAnimationComponent::Render()
{
	AnimationComponent::Render();

}

void KatanaAnimationComponent::Term()
{
	AnimationComponent::Term();
}

void KatanaAnimationComponent::HandleMessage(const IEventMessage& _msg)
{

}

void KatanaAnimationComponent::Reset()
{
	AnimationComponent::Reset();
}

void KatanaAnimationComponent::OnAnimationEvent(const AnimationEvent& _animEvent)
{
}

void KatanaAnimationComponent::RegisterKatanaAnimation()
{

}

void KatanaAnimationComponent::HandleKatanaSwingAnimation()
{
		
}
