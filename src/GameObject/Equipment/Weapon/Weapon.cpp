#include "GameObject/Equipment/Weapon/Weapon.h"

Weapon::Weapon() :Equipment(nullptr)
{

}

Weapon::Weapon(IEquipOwnerView* _equipOwnerView) : Equipment(_equipOwnerView)
{

}

void Weapon::Init()
{
	Equipment::Init();
}

void Weapon::Update()
{
	Equipment::Update();
}

void Weapon::Render()
{
	Equipment::Render();
}

void Weapon::Term()
{
	Equipment::Term();
}


void Weapon::Attack()
{

}

void Weapon::EndAttack()
{
	mode_ = WeaponMode::EQUIPPED;
}

bool Weapon::CanAttack() const
{
	switch (mode_)
	{
	case WeaponMode::EQUIPPED:
		return true;
	case WeaponMode::DROPPED:
		return false;
	default:
		return false;
	}
}

Lib::Math::Vector2f Weapon::GetPosition() const
{
	if (!transformComponent_)
		return { 0.0f,0.0f };
	return transformComponent_->GetPosition();
}

float Weapon::GetPositionX() const
{
	return GetPosition().x;
}

float Weapon::GetPositionY() const
{
	return GetPosition().y;
}

Direction Weapon::GetDirection() const
{
	if (!transformComponent_)
		return Direction::NONE;

	return transformComponent_->GetDirection();
}

EquipmentType Weapon::GetEquipmentType() const
{
	return equipment_;
}

WeaponMode Weapon::GetMode() const
{
	return mode_;
}

void Weapon::Equip()
{
	mode_ = WeaponMode::EQUIPPED;
}

bool Weapon::IsAttacking() const
{
	return mode_ == WeaponMode::ATTACKING;
}


