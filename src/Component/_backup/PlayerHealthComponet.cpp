#include "Component/PlayerHealthComponent.h"

int PlayerHealthComponent::GetInvinvibilityFrames() const
{
	return invincibilityFrames_;
}

int PlayerHealthComponent::SetHp(const int _new)
{
	if (_new<0)
	{
		hp_ = 0;
	}

	hp_ = _new;
}

int PlayerHealthComponent::SetHpMax(const int _new)
{
	if (_new < 0)
	{
		hpMax_ = 0;
	}

	hpMax_ = _new;
}

int PlayerHealthComponent::SetInvinvibilityFrames(const int _new)
{
	if (_new < 0)
	{
		invincibilityFrames_ = 0;
	}

	invincibilityFrames_ = _new;
}

PlayerHealthComponent::PlayerHealthComponent(bool _isActive, Player* player): Component(_isActive),
                                                                              player_(player),hp_(0),hpMax_(0),invincibilityFrames_(0)
{
}

PlayerHealthComponent::PlayerHealthComponent(Player* player): player_(player), hp_(0), hpMax_(0), invincibilityFrames_(0)
{
}

int PlayerHealthComponent::GetHp() const
{
	return hp_;
}

int PlayerHealthComponent::GetHpMax() const
{
	return  hpMax_;
}