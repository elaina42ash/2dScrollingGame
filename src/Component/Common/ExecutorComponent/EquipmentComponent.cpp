#include "Component/Common/ExecutorComponent/Class/EquipmentComponent.h"

#include "GameObject/DroppedObject/DroppedKatana.h"
#include "GameObject/Equipment/Weapon/Katana.h"
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

void EquipmentComponent::Equip(EquipmentSlotID _slotId, std::shared_ptr<IEquipment> _equipment)
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

	std::shared_ptr<IWeapon> weapon = std::dynamic_pointer_cast<IWeapon>(it->second);

	if (!weapon)
		return;

	activeSlotID_ = _slotID;
	activeWeapon = weapon;
}

void EquipmentComponent::SwitchToNextWeapon()
{
	if (equipmentMap_.empty())
		return;

	auto currentIt = equipmentMap_.find(activeSlotID_);
	auto it = currentIt;

	do
	{
		if (it == equipmentMap_.end() || std::next(it) == equipmentMap_.end())
			it = equipmentMap_.begin();
		else
			++it;

		std::shared_ptr<IWeapon> nextWeapon = std::dynamic_pointer_cast<IWeapon>(it->second);
		if (nextWeapon)
		{
			SwitchWeapon(it->first);
			return;
		}

	} while (it != currentIt);
}

std::shared_ptr<IEquipment> EquipmentComponent::FindEquipment(EquipmentSlotID _slotID)
{
	auto it = equipmentMap_.find(_slotID);
	if (it == equipmentMap_.end())
		return nullptr;
	return it->second;
}

std::shared_ptr<IWeapon> EquipmentComponent::FindWeapon(EquipmentSlotID _slotID)
{
	std::shared_ptr<IEquipment> equipment = FindEquipment(_slotID);

	if (!equipment)
		return nullptr;

	std::shared_ptr<IWeapon> weapon = std::dynamic_pointer_cast<IWeapon>(equipment);
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
	return activeSlotID_;
}

void EquipmentComponent::TakeDroppedWeapon(const char* _name, DroppedObject* _droppedObject)
{
	if (strcmp(_name, "Sword") == 0)
	{
		DroppedSword* droppedSword = dynamic_cast<DroppedSword*>(_droppedObject);

		if (!droppedSword)
			return;

		std::shared_ptr<Sword> sword = droppedSword->GetSword();
		if (!sword)
			return;

		sword->SetOwner(dynamic_cast<Player*>(this->GetOwner()));

		for (int slot = static_cast<int>(EquipmentSlotType::WEAPON_1);
			slot <= static_cast<int>(EquipmentSlotType::WEAPON_2); ++slot)
		{
			if (equipmentMap_.find(slot) == equipmentMap_.end())
			{

				Equip(slot, sword);
				SwitchWeapon(slot);

				_droppedObject->Disable();
				ICollisionComponent* collisionComponent = _droppedObject->GetComponent<ICollisionComponent>();
				if (collisionComponent)
					collisionComponent->DisableCollider();

				return;
			}
		}
	}

	if (strcmp(_name, "Katana") == 0)
	{
		DroppedKatana* droppedKatana = dynamic_cast<DroppedKatana*>(_droppedObject);

		if (!droppedKatana)
			return;

		std::shared_ptr<Katana> katana = droppedKatana->GetKatana();
		if (!katana)
			return;

		katana->SetOwner(dynamic_cast<Player*>(this->GetOwner()));

		for (int slot = static_cast<int>(EquipmentSlotType::WEAPON_1);
			slot <= static_cast<int>(EquipmentSlotType::WEAPON_2); ++slot)
		{
			if (equipmentMap_.find(slot) == equipmentMap_.end())
			{

				Equip(slot, katana);
				SwitchWeapon(slot);

				_droppedObject->Disable();
				ICollisionComponent* collisionComponent = _droppedObject->GetComponent<ICollisionComponent>();
				if (collisionComponent)
					collisionComponent->DisableCollider();

				return;
			}
		}
	}
}

void EquipmentComponent::DropWeapon()
{
	// アクティブな武器が無ければ処理しない
	if (!activeWeapon)
		return;

	// Sword または Katana を判定
	std::shared_ptr<Sword> sword = std::dynamic_pointer_cast<Sword>(activeWeapon);
	std::shared_ptr<Katana> katana = std::dynamic_pointer_cast<Katana>(activeWeapon);

	if (!sword && !katana)
		return;

	// プレイヤー取得
	Player* player = dynamic_cast<Player*>(this->GetOwner());
	if (!player)
		return;

	// 現在位置取得
	Vector2f position = GetComponent<ITransformComponent>()->GetPosition();
	switch (player->GetDirection())
	{
	case Direction::RIGHT:
	case Direction::LEFT:
		position.y += 20.0f;
		break;
	}

	// 落下オブジェクトを生成
	if (sword)
		player->AccessSceneGameplayApi()->CreateDroppedObject("Sword", position);
	if (katana)
		player->AccessSceneGameplayApi()->CreateDroppedObject("Katana", position);

	// ----------------------------
	// activeWeapon に対応する slot を検索して解除
	// ----------------------------
	EquipmentSlotID slot = -1;
	for (std::unordered_map<EquipmentSlotID, std::shared_ptr<IEquipment>>::const_iterator it = equipmentMap_.begin();
		it != equipmentMap_.end(); ++it)
	{
		std::shared_ptr<IWeapon> weaponInSlot = std::dynamic_pointer_cast<IWeapon>(it->second);
		if (weaponInSlot == activeWeapon)
		{
			slot = it->first;
			break;
		}
	}

	// 該当スロットを見つけた場合にのみ削除処理を行う
	if (slot != -1)
	{
		// 装備を解除
		Unequipped(slot);

		// アクティブスロットだった場合、状態をリセット
		if (slot == activeSlotID_)
		{
			activeWeapon = nullptr;
			activeSlotID_ = static_cast<int>(EquipmentType::NONE);
		}

		// 次の武器に切り替え
		SwitchToNextWeapon();
	}
}



void EquipmentComponent::Reset()
{
	ExecutorComponent::Reset();
}

const std::shared_ptr<const IWeapon> EquipmentComponent::GetActiveWeapon() const
{
	return activeWeapon;
}

EquipmentComponent::EquipmentSlotID EquipmentComponent::GetActiveWeaponID() const
{
	return activeSlotID_;
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
	for (auto it = equipmentMap_.begin(); it != equipmentMap_.end(); ++it)
	{
		if (it->second)
			it->second->Update();
	}
}

