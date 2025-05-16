#pragma once
#include "Lib/Math/TVector2.h"

class ILineSensor
{
public:
	virtual ~ILineSensor() = default;

	virtual bool Detected(const Lib::Math::Vector2f& _targetPos) const = 0;

	virtual Lib::Math::Vector2f GetEndPoint() const = 0;

	virtual Lib::Math::Vector2f GetPosition() const = 0;

	virtual void SetPosition(const Lib::Math::Vector2f& _newPos) = 0;

	virtual void SetRayVec(const Lib::Math::Vector2f& _newVec) = 0;

	virtual float GetEpsilon() const = 0;
};
