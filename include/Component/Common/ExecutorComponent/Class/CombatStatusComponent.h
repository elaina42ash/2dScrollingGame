#pragma once
#include "ExecutorComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ICombatStatusComponent.h"
#pragma warning(push)
#pragma warning(disable:4250)
class CombatStatusComponent : public ExecutorComponent, public ICombatStatusComponent
{
protected:
	// 無敵中の残りフレーム
	int invincibilityFrames_ = 0;
public:
	explicit CombatStatusComponent(bool _isActive,IMessenger* _messenger);

	CombatStatusComponent(IMessenger* _messenger);

	int GetRemainingInvincibilityFrames() const override final;

	void Init() override;

	void UpdateInvincibility();

	void Update() override;

	void Render() override;

	void Term() override;

	bool IsInvincible() const override final;


protected:
	void Reset() override;
};
#pragma warning(pop)