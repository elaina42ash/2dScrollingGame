#pragma once
#include "Weapon.h"

#pragma warning(push)
#pragma warning(disable:4250)
class Sword : public Weapon
{
public:
	Sword();

	explicit Sword(IEquipOwnerView* _equipOwnerView);

	~Sword() override;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void Attack() override;

	void EndAttack() override;

	void HandleMessage(const IEventMessage& _msg) override;

private:
	void InitializeSwordComponents();
};
#pragma warning(pop)


