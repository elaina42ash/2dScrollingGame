#pragma once
#include "ExecutorComponent.h"
#include "IEquipOwnerView.h"
#include "Component/Common/ExecutorComponent/Interface/IEquipmentComponent.h"
#include "GameObject/Equipment/IEquipment.h"
#include "GameObject/Equipment/Weapon/IWeapon.h"
#pragma warning(push)
#pragma warning(disable:4250)
class EquipmentComponent : public ExecutorComponent,public IEquipmentComponent
{
	using EquipmentSlotID = int;

private:

	std::unordered_map<EquipmentSlotID, IEquipment*> equipmentMap_;

protected:
	Inject<IEquipOwnerView> equipOwnerView_;

	EquipmentSlotID activeWeaponID_ = static_cast<int>(EquipmentType::NONE);

	IWeapon* activeWeapon = nullptr;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

	void Equip(EquipmentSlotID _slotId,IEquipment* _equipment);

	void Unequipped(EquipmentSlotID _slotId);

	void SwitchWeapon(EquipmentSlotID _slotID);

	IEquipment* FindEquipment(EquipmentSlotID _slotID);

	IWeapon* FindWeapon(EquipmentSlotID _slotID);

	bool IsAttacking() override;

	bool GetActiveWeaponID_() const override;

protected:
	explicit EquipmentComponent(bool _isActive, IEquipOwnerView* _equipOwnerView_,IMessenger* _messenger);

	void Reset() override;

	const IWeapon* const GetActiveWeapon() const;

	EquipmentSlotID GetActiveWeaponID() const;

private:
	void InitEquipments();

	void UpdateEquipments();

	void RenderEquipments();

	void TermEquipments();
};
#pragma warning(pop)