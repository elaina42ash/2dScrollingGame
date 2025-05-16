#pragma once
#include "Component/Common/ExecutorComponent/Class/AnimationComponent.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class SwordAnimationComponent : public AnimationComponent
{
private:
	Inject<IWeaponView> swordView_;

	bool hasTriggeredAttack_ = false;
public:
	SwordAnimationComponent(bool _isActive, IMessenger* messenger_, IWeaponView* _swordView);

	SwordAnimationComponent(IMessenger* messenger_, IWeaponView* _swordView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;

	void OnAnimationEvent(const AnimationEvent& _animEvent) override;

private:
	void RegisterSwordAnimation();

	void HandleSwordSwingAnimation();
};
#pragma warning(pop)