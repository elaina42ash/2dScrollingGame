#include "Component/Sword/ExecutorComponent/Class/SwordTransformComponent.h"

SwordTransformComponent::SwordTransformComponent(bool _isActive, IWeaponView* _swordView, IEquipOwnerView* _equipOwnerView, IMessenger* _messenger) : TransformComponent(_isActive, _messenger), swordView_(_swordView), equipOwnerView_(_equipOwnerView)
{
}

SwordTransformComponent::SwordTransformComponent(IWeaponView* _swordView, IEquipOwnerView* _equipOwnerView, IMessenger* _messenger) : TransformComponent(_messenger), swordView_(_swordView),
equipOwnerView_(_equipOwnerView)
{
}

void SwordTransformComponent::Init()
{
	TransformComponent::Init();

	if (equipOwnerView_)
		ChangeDirection(equipOwnerView_->GetDirection());
}

void SwordTransformComponent::Update()
{
	if (equipOwnerView_)
		MoveTo(equipOwnerView_->GetPosition());
	if (equipOwnerView_)
		ChangeDirection(equipOwnerView_->GetDirection());

	TransformComponent::Update();

	Reset();
}

void SwordTransformComponent::Render()
{
	TransformComponent::Update();
}

void SwordTransformComponent::Term()
{
	TransformComponent::Term();
}

void SwordTransformComponent::HandleMessage(const IEventMessage& _msg)
{

}

void SwordTransformComponent::Reset()
{
	TransformComponent::Reset();
}
