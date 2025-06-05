#include "GameObject/Equipment/Equipment.h"

Equipment::Equipment(IEquipOwnerView* _equipOwnerView): equipOwnerView_(_equipOwnerView)
{
}

void Equipment::Init()
{
	GameObject::Init();
}

void Equipment::Update()
{
	GameObject::Update();
}

void Equipment::Render()
{
	GameObject::Render();
}

void Equipment::Term()
{
	GameObject::Term();
}

EquipmentStatus Equipment::GetEquipmentStatus()
{
	return equipmentStatus_;
}

void Equipment::SetOwner(Player* _player)
{
	equipOwnerView_.Bind(_player);
}

void Equipment::SetEquipmentStatus(const EquipmentStatus& _status)
{
	equipmentStatus_ = _status;
}
