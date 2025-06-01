#pragma once
#include "ExecutorComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IHealthComponent.h"
#pragma warning(push)
#pragma warning(disable:4250)
class HealthComponent : public ExecutorComponent , public IHealthComponent
{
protected:
	int maxHp_ = 0;

	int hp_ = maxHp_;

public:
	int GetHp() const override final;

	int GetMaxHp() const override final;

	float GetNormalizedHp() const override final;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	bool IsDead() const override final;

protected:
	explicit HealthComponent(bool _isActive,IMessenger* _messenger);

	void Reset() override;

protected:
	virtual void SetHp(int _newHp);

	void SetMaxHp(int _newMaxHp);
};
#pragma warning(pop)