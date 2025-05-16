#pragma once
#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class SwordCollisionComponent: public CollisionComponent
{
private:
	// 衝突範囲テーブル（向き別）振り下ろし後のパターンの衝突範囲
	const Fwk::Collision::Rect hitRects[2] = {
		{{68.0f,0.0f},64.0f,32.0f}, // right
	{{-68.0f,0.0f},64.0f,32.0f }, // left
	};

	// 衝突範囲テーブル２（向き別）振り下ろし中（斜めの時）の衝突範囲
	const Fwk::Collision::Rect hitRects2[2] = {
	{{70.0f,42.0f},54.0f,32.0f}, //right
	{{-70.0f,42.0f},54.0f,32.0f}, // left
	};

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