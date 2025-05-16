#pragma once
#include "Component/Common/ExecutorComponent/Class/EquipmentComponent.h"
#include "Player/IPlayerView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class PlayerEquipmentComponent : public EquipmentComponent
{
private:
	Inject<IPlayerView> playerView_;
public:
	explicit PlayerEquipmentComponent(bool _isActive, IPlayerView* playerView_,IEquipOwnerView* _equipOwnerView,IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;

private:
	void Attack();
};
#pragma warning(pop)
