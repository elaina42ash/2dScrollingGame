#pragma once
#include "Component/Common/ExecutorComponent/Class/AnimationComponent.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class KatanaAnimationComponent : public AnimationComponent
{
private:
	Inject<IWeaponView> weaponView_;

	bool hasTriggeredAttack_ = false;
public:
	KatanaAnimationComponent(bool _isActive, IMessenger* messenger_, IWeaponView* _weaponView);

	KatanaAnimationComponent(IMessenger* messenger_, IWeaponView* _weaponView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;

	void OnAnimationEvent(const AnimationEvent& _animEvent) override;

private:
	void RegisterKatanaAnimation();

	void HandleKatanaSwingAnimation();
};
#pragma warning(pop)