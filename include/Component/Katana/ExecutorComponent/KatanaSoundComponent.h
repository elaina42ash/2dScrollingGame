#pragma once
#include "Component/Common/ExecutorComponent/Class/SoundComponent.h"
#include "GameObject/Equipment/Weapon/IWeaponView.h"


#pragma warning(push)
#pragma warning(disable:4250)
class KatanaSoundComponent : public SoundComponent
{
private:
	Inject<IWeaponView> weaponView_;

public:
	explicit KatanaSoundComponent(bool _isActive, IWeaponView* _weaponView,IMessenger* _messenger);

	void Init() override;

	void Update() override;


	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)