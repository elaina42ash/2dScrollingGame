#pragma once
#include "GameMath.h"
#include "ILineSensor.h"

class LineSensor : public  ILineSensor
{
private:
	Lib::Math::Vector2f rayVec_ = { 0.0f,0.0f };

	Lib::Math::Vector2f position_ = { 0.0f,0.0f };

	const float epsilon_ = 0.5f; // 可调精度阈值

public:
	LineSensor(const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position, float _epsilon);

	LineSensor(const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position);

	LineSensor() = default;

	bool Detected(const Lib::Math::Vector2f& _targetPos) const override;

	Lib::Math::Vector2f GetEndPoint() const override;

	Lib::Math::Vector2f GetPosition() const override;

	void SetPosition(const Lib::Math::Vector2f& _newPos) override;

	void SetRayVec(const Lib::Math::Vector2f& _newVec) override;

	float GetEpsilon() const override;
};
