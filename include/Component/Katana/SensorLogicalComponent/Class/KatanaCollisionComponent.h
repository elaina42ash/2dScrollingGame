#pragma once
#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class KatanaCollisionComponent: public CollisionComponent
{
private:
	Inject<IWeaponView> weaponView_;
public:
	KatanaCollisionComponent(bool _isActive, IMessenger* _messenger, IWeaponView* _weaponView);

	explicit KatanaCollisionComponent(IMessenger* _messenger, IWeaponView* _weaponView);

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