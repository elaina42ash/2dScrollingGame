#pragma once
#include "IEquipment.h"
#include "IEquipOwnerView.h"
#include "Inject.h"
#include "GameObject/GameObject.h"

#pragma warning(push)
#pragma warning(disable:4250)
class Equipment :public GameObject,public IEquipment
{
private:
	EquipmentStatus equipmentStatus_ = EquipmentStatus::NONE;

protected:
	Inject<IEquipOwnerView> equipOwnerView_;

	EquipmentType equipment_ = EquipmentType::NONE;
public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	EquipmentStatus GetEquipmentStatus() override final;

	void SetOwner(Player* _player) override;

protected:
	explicit Equipment(IEquipOwnerView* _equipOwnerView);

	Equipment() = default;

private:
	void SetEquipmentStatus(const EquipmentStatus& _status);
};
#pragma warning(pop)
