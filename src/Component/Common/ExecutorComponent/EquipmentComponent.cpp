#include "Component/Common/ExecutorComponent/Class/EquipmentComponent.h"
#include "GameObject/Equipment/Weapon/Sword.h"

EquipmentComponent::EquipmentComponent(bool _isActive, IEquipOwnerView* _equipOwnerView_, IMessenger* _messenger) : ExecutorComponent(_isActive, _messenger), equipOwnerView_(_equipOwnerView_)
{
}

void EquipmentComponent::Init()
{
	ExecutorComponent::Init();

	InitEquipments();
}

void EquipmentComponent::Update()
{
	ExecutorComponent::Update();

	UpdateEquipments();
}

void EquipmentComponent::Render()
{
	ExecutorComponent::Render();

	RenderEquipments();
}

void EquipmentComponent::Term()
{
	ExecutorComponent::Term();

	TermEquipments();
}

void EquipmentComponent::HandleMessage(const IEventMessage& _msg)
{

}

void EquipmentComponent::Equip(EquipmentSlotID _slotId, IEquipment* _equipment)
{
	auto it = equipmentMap_.find(_slotId);
	if (it != equipmentMap_.end())
		return;
	equipmentMap_.insert({ _slotId,_equipment });
}

void EquipmentComponent::Unequipped(EquipmentSlotID _slotId)
{
	auto it = equipmentMap_.find(_slotId);
	if (it == equipmentMap_.end())
		return;
	equipmentMap_.erase(_slotId);
}

void EquipmentComponent::SwitchWeapon(EquipmentSlotID _slotID)
{
	auto it = equipmentMap_.find(_slotID);
	if (it == equipmentMap_.end())
	return;

	IWeapon* weapon = dynamic_cast<IWeapon*>(it->second);

	if (!weapon)
	return;

	activeWeaponID_ = _slotID;
	activeWeapon = weapon;
}

void EquipmentComponent::SwitchToNextWeapon()
{
	if (equipmentMap_.empty())
		return;

	auto currentIt = equipmentMap_.find(activeWeaponID_);
	auto it = currentIt;

	do
	{
		if (it == equipmentMap_.end() || std::next(it) == equipmentMap_.end())
			it = equipmentMap_.begin();
		else
			++it;

		IWeapon* nextWeapon = dynamic_cast<IWeapon*>(it->second);
		if (nextWeapon)
		{
			SwitchWeapon(it->first);
			return;
		}

	} while (it != currentIt);
}

IEquipment* EquipmentComponent::FindEquipment(EquipmentSlotID _slotID)
{
	auto it = equipmentMap_.find(_slotID);
	if (it == equipmentMap_.end())
		return nullptr;
	return it->second;
}

IWeapon* EquipmentComponent::FindWeapon(EquipmentSlotID _slotID)
{
	IEquipment* equipment = FindEquipment(_slotID);

	if (!equipment)
		return nullptr;

	IWeapon* weapon = dynamic_cast<IWeapon*>(equipment);
	if (!weapon)
		return nullptr;

	return weapon;
}

bool EquipmentComponent::IsAttacking()
{
	if (!activeWeapon)
		return false;
	return activeWeapon->IsAttacking();
}

bool EquipmentComponent::GetActiveWeaponID_() const
{
	return activeWeaponID_;
}

void EquipmentComponent::Reset()
{
	ExecutorComponent::Reset();
}

const IWeapon* const EquipmentComponent::GetActiveWeapon() const
{
	return activeWeapon;
}

EquipmentComponent::EquipmentSlotID EquipmentComponent::GetActiveWeaponID() const
{
	return activeWeaponID_;
}

void EquipmentComponent::InitEquipments()
{
	for (auto it = equipmentMap_.begin(); it != equipmentMap_.end(); ++it)
	{
		if (it->second)
			it->second->Init();
	}
}

void EquipmentComponent::RenderEquipments()
{
	for (auto it = equipmentMap_.begin(); it != equipmentMap_.end(); ++it)
	{
		if (it->second)
			it->second->Render();
	}
}

void EquipmentComponent::TermEquipments()
{
	for (auto it = equipmentMap_.begin(); it != equipmentMap_.end(); ++it)
	{
		if (it->second)
			it->second->Term();
	}
}

void EquipmentComponent::UpdateEquipments()
{
	for (auto it = equipmentMap_.begin();it!=equipmentMap_.end();++it)
	{
		if (it->second)
			it->second->Update();
	}
}

