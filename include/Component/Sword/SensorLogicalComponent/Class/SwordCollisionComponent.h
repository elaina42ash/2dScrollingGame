#pragma once
#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class SwordCollisionComponent: public CollisionComponent
{
private:
	Inject<IWeaponView> swordView_;
public:
	SwordCollisionComponent(bool _isActive, IMessenger* _messenger, IWeaponView* _swordView);

	explicit SwordCollisionComponent(IMessenger* _messenger, IWeaponView* _swordView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;


protected:

	void Reset() override;

	void OnCollisionEx(const Fwk::Collision::CollisionEvent& _collisionEvent) override;
};
#pragma warning(pop)