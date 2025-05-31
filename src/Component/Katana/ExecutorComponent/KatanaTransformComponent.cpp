
#include "Component/Katana/ExecutorComponent/KatanaTransformComponent.h"

KatanaTransformComponent::KatanaTransformComponent(bool _isActive, IWeaponView* _weaponView, IEquipOwnerView* _equipOwnerView, IMessenger* _messenger) : TransformComponent(_isActive, _messenger), weaponView_(_weaponView), equipOwnerView_(_equipOwnerView)
{
}

KatanaTransformComponent::KatanaTransformComponent(IWeaponView* _weaponView, IEquipOwnerView* _equipOwnerView, IMessenger* _messenger) : TransformComponent(_messenger), weaponView_(_weaponView),
equipOwnerView_(_equipOwnerView)
{
}

void KatanaTransformComponent::Init()
{
	TransformComponent::Init();

	if (equipOwnerView_)
		ChangeDirection(equipOwnerView_->GetDirection());
}

void KatanaTransformComponent::Update()
{
	if (equipOwnerView_)
		MoveTo(equipOwnerView_->GetPosition());
	if (equipOwnerView_)
		ChangeDirection(equipOwnerView_->GetDirection());

	TransformComponent::Update();

	Reset();
}

void KatanaTransformComponent::Render()
{
	TransformComponent::Update();
}

void KatanaTransformComponent::Term()
{
	TransformComponent::Term();
}

void KatanaTransformComponent::HandleMessage(const IEventMessage& _msg)
{

}

void KatanaTransformComponent::Reset()
{
	TransformComponent::Reset();
}
