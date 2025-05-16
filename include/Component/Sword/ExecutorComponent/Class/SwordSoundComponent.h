#pragma once
#include "Component/Common/ExecutorComponent/Class/SoundComponent.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"


#pragma warning(push)
#pragma warning(disable:4250)
class SwordSoundComponent : public SoundComponent
{
private:
	Inject<IWeaponView> swordView_;

public:
	explicit SwordSoundComponent(bool _isActive, IWeaponView* _swordView,IMessenger* _messenger);

	void Init() override;

	void Update() override;


	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)