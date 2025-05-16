#pragma once
#include "GameDef.h"
#include "Lib/Math/TVector2.h"

class IPlayerView
{
public:
	virtual  ~IPlayerView() = default;

	virtual Direction GetDirection() const = 0;

	virtual Lib::Math::Vector2f GetVelocity() const = 0;

	virtual float GetVelocityX() const = 0;

	virtual float GetVelocityY() const = 0;

	virtual Lib::Math::Vector2f GetPosition() const = 0;

	virtual  float GetPositionX() const = 0;

	virtual float GetPositionY() const = 0;

	virtual bool IsAlive() const = 0;

	virtual bool IsDead() const = 0;

	virtual bool IsReachedGoal() const = 0;

	virtual int GetHp() const = 0;

	virtual float GetNormalizedHp() const = 0;

	virtual bool Grounded() const = 0;

	virtual int IsInVincible() const = 0;

	virtual bool IsAttacking() const = 0;

	virtual bool IsStageCleared() const = 0;

	virtual int GetRemainingInvincibleFrames() const = 0;
};

