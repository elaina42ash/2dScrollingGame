#pragma once
#include "IEquipOwnerView.h"
#include "Component/Common/ExecutorComponent/Class/TransformComponent.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class SwordTransformComponent : public TransformComponent
{
private:
	Inject<IWeaponView> swordView_;
	Inject<IEquipOwnerView> equipOwnerView_;
public:
	SwordTransformComponent(bool _isActive, IWeaponView* _swordView,IEquipOwnerView* _equipOwnerView,IMessenger* _messenger);

	SwordTransformComponent(IWeaponView* _swordView, IEquipOwnerView* _equipOwnerView, IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;

private:

};
#pragma warning(pop)