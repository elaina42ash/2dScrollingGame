#pragma once
#include "Component.h"
#include "Event/Listener/IMessageListener.h"

class Player;
class PlayerHealthComponent : public Component,public IMessageListener
{
private:
	// 体力
	int hp_;

	// 体力(最大値)
	int hpMax_;

	// 無敵中の残りフレーム
	int invincibilityFrames_;

	Player* player_;

private:
	int SetHp(const int _new);

	int SetHpMax(const int _new);

	int SetInvinvibilityFrames(const int _new);

public:
	PlayerHealthComponent(bool _isActive, Player* player);

	explicit PlayerHealthComponent(Player* player);

	int GetHp() const;

	int GetHpMax() const;

	int GetInvinvibilityFrames() const;

	void Init() override
	{
		
	}
	void Update() override
	{
		
	}
	void Render() override
	{
		
	}
	void Term() override
	{
		
	}
	void HandleMessage(const IEventMessage& _msg) override;
};
