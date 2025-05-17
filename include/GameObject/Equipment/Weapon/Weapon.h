#pragma once
#include "IWeapon.h"
#include "IWeaponView.h"
#include "Component/Common/ExecutorComponent/Interface/IAnimationComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ISoundComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "GameObject/Equipment/Equipment.h"


#pragma warning(push)
#pragma warning(disable:4250)
class Weapon : public Equipment, public IWeapon, public IWeaponView
{
protected:
	ITransformComponent* transformComponent_ = nullptr;
	ICollisionComponent* collisionComponent_ = nullptr;
	IAnimationComponent* animationComponent_ = nullptr;
	ISoundComponent* soundComponent_ = nullptr;

	WeaponMode mode_ = WeaponMode::NONE;

public:
	virtual ~Weapon() override =default;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void Attack() override;

	void EndAttack() override;

	bool CanAttack() const override final;

	Lib::Math::Vector2f GetPosition() const override final;

	float GetPositionX() const override final;

	float GetPositionY() const override final;

	Direction GetDirection() const override final;

	EquipmentType GetEquipmentType() const override final;

	void Equip() override final;

	bool IsAttacking() const override final;

	WeaponMode GetMode() const override final;

protected:
	Weapon();

	explicit Weapon(IEquipOwnerView* _equipOwnerView);
};
#pragma warning(pop)
