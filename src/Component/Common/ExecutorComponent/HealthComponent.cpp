#include "Component/Common/ExecutorComponent/Class/HealthComponent.h"
#include "GameMath.h"

HealthComponent::HealthComponent(bool _isActive, IMessenger* _messenger): ExecutorComponent(_isActive, _messenger)
{
}

int HealthComponent::GetHp() const
{
	return 	GameMath::Clamp(hp_, 0, GetMaxHp());
}

int HealthComponent::GetMaxHp() const
{

	return 	GameMath::Clamp(maxHp_, 0, 99999);
}

float HealthComponent::GetNormalizedHp() const
{
	return static_cast<float>(GetHp()) / static_cast<float>(GetMaxHp());
}

void HealthComponent::Init()
{
	ExecutorComponent::Init();
}

void HealthComponent::Update()
{
	ExecutorComponent::Update();
}

void HealthComponent::Render()
{
	ExecutorComponent::Render();
}

void HealthComponent::Term()
{
	ExecutorComponent::Term();
}

bool HealthComponent::IsDead() const
{
	if (GetHp() <= 0)
		return true;
	return false;
}

void HealthComponent::Reset()
{
	ExecutorComponent::Reset();
}

void HealthComponent::SetHp(const int _newHp)
{
	GameMath::Clamp(_newHp, 0, maxHp_);
	hp_ = _newHp;
}

void HealthComponent::SetMaxHp(const int _newMaxHp)
{
	GameMath::Clamp(_newMaxHp, 0, 99999);
	maxHp_ = _newMaxHp;
}
