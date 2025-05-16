#include "Component/Common/ExecutorComponent/Class/CombatStatusComponent.h"

CombatStatusComponent::CombatStatusComponent(bool _isActive, IMessenger* _messenger): ExecutorComponent(_isActive, _messenger)
{
}

CombatStatusComponent::CombatStatusComponent(IMessenger* _messenger):ExecutorComponent(_messenger)
{
		
}

int CombatStatusComponent::GetRemainingInvincibilityFrames() const
{
	return invincibilityFrames_;
}

void CombatStatusComponent::Init()
{
	ExecutorComponent::Init();
}

void CombatStatusComponent::UpdateInvincibility()
{
	// 無敵フレーム数が0であれば何もしない
	if (invincibilityFrames_ == 0)
	{
		return;
	}

	// 無敵フレーム数を減らす
	--invincibilityFrames_;
}

void CombatStatusComponent::Update()
{
	ExecutorComponent::Update();

	UpdateInvincibility();
}

void CombatStatusComponent::Render()
{
	ExecutorComponent::Render();
}

void CombatStatusComponent::Term()
{
	ExecutorComponent::Term();
}

bool CombatStatusComponent::IsInvincible() const
{
	return invincibilityFrames_ > 0;
}

void CombatStatusComponent::Reset()
{
	ExecutorComponent::Reset();
}
