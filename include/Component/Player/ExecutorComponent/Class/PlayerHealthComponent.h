#pragma once
#include "Component/Common/ExecutorComponent/Class/HealthComponent.h"

#pragma warning(push)
#pragma warning(disable:4250)
class PlayerHealthComponent : public HealthComponent
{
	using HpChangedCallback = std::function<void(float)>;
private:
	HpChangedCallback onHpChangedCallback_;

public:
	explicit PlayerHealthComponent(bool _isActive,IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

	void TakeDamage(int _incomingDamage);

	void SetOnHpChanged(HpChangedCallback _callback);

protected:
	void SetHp(int _newHp) override;

	void Reset() override;

};
#pragma warning(pop)