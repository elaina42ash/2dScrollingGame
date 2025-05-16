#pragma once
#include "Component/Common/ExecutorComponent/Class/CombatStatusComponent.h"
#pragma warning(push)
#pragma warning(disable:4250)
class PlayerCombatStatusComponent : public CombatStatusComponent
{
public:
	explicit PlayerCombatStatusComponent(bool _isActive,IMessenger* _messenger);

	PlayerCombatStatusComponent(IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)