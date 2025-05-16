#include "Sensor/LineSensor.h"

LineSensor::LineSensor(const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position, float _epsilon): rayVec_(_rayVec),
	position_(_position),
	epsilon_(_epsilon)
{
}

LineSensor::LineSensor(const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position): rayVec_(_rayVec),
	position_(_position)
{
}

bool LineSensor::Detected(const Lib::Math::Vector2f& _targetPos) const
{
	// 线段起点和终点
	Lib::Math::Vector2f start = position_;
	Lib::Math::Vector2f end = position_ + rayVec_;
	Lib::Math::Vector2f segment = end - start;

	Lib::Math::Vector2f toPoint = _targetPos - start;

	// 投影到射线方向上，算出投影长度
	float segmentLengthSq = GameMath::LengthSquared(segment);
	float projection = GameMath::Dot(toPoint, segment);

	// 不在线段范围内（投影长度为负或超过长度）
	if (projection < 0 || projection > segmentLengthSq)
		return false;

	// 计算点到线的最短距离
	float distanceSq = GameMath::LengthSquared((toPoint - (segment * (projection / segmentLengthSq))));
	return distanceSq <= epsilon_ * epsilon_;
}

Lib::Math::Vector2f LineSensor::GetEndPoint() const
{
	return position_ + rayVec_;
}

Lib::Math::Vector2f LineSensor::GetPosition() const
{
	return position_;
}

void LineSensor::SetPosition(const Lib::Math::Vector2f& _newPos)
{
	position_ = _newPos;
}

void LineSensor::SetRayVec(const Lib::Math::Vector2f& _newVec)
{
	rayVec_ = _newVec;
}

float LineSensor::GetEpsilon() const
{
	return epsilon_;
}
