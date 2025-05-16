#include "Component/Player/ExecutorComponent/Class/PlayerEquipmentComponent.h"
#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "GameObject/Equipment/Weapon/Sword.h"

PlayerEquipmentComponent::PlayerEquipmentComponent(bool _isActive, IPlayerView* playerView_, IEquipOwnerView* _equipOwnerView, IMessenger* _messenger) : EquipmentComponent(_isActive, _equipOwnerView, _messenger), playerView_(playerView_)
{
}

void PlayerEquipmentComponent::Init()
{
	EquipmentComponent::Init();

	//TODO:hard coding
	Sword* sword = new Sword(equipOwnerView_.Injected());
	if (sword)
	{
		sword->Init();
		Equip(static_cast<int>(EquipmentSlotType::WEAPON_1), sword);
	}

	SwitchWeapon(static_cast<int>(EquipmentSlotType::WEAPON_1));

}

void PlayerEquipmentComponent::Update()
{
	EquipmentComponent::Update();

	Reset();
}

void PlayerEquipmentComponent::Render()
{
	EquipmentComponent::Render();
}

void PlayerEquipmentComponent::Term()
{
	EquipmentComponent::Term();
}

void PlayerEquipmentComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartAttackSemMsg* startAttackSemMsg = TypeidSystem::SafeCast<StartAttackSemMsg>(&_msg);

	if (startAttackSemMsg)
	{
		Attack();
	}
}

void PlayerEquipmentComponent::Reset()
{
	EquipmentComponent::Reset();
}

void PlayerEquipmentComponent::Attack()
{
	if (activeWeapon == nullptr || activeWeaponID_ == static_cast<int>(EquipmentType::NONE))
		return;
	activeWeapon->Attack();
}
