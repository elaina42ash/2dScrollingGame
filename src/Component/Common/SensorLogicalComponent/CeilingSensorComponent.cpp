#include "Component/Common/SensorLogicalComponent/Class/CeilingSensorComponent.h"
#include "Sensor/LineSensor.h"

CeilingSensorComponent::CeilingSensorComponent(bool _isActive, IMessenger* _messenger,
                                               const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position): SensorLogicalComponent(_isActive, _messenger)
{
	lineSensor_ = new LineSensor(_rayVec, _position);
}

CeilingSensorComponent::CeilingSensorComponent(IMessenger* _messenger, const Lib::Math::Vector2f& _rayVec,
	const Lib::Math::Vector2f& _position): SensorLogicalComponent(_messenger)
{
	lineSensor_ = new LineSensor(_rayVec, _position);
}

CeilingSensorComponent::~CeilingSensorComponent()
{
	if (lineSensor_)
	{
		delete lineSensor_;
		lineSensor_ = nullptr;
	}
}

void CeilingSensorComponent::Init()
{
	SensorLogicalComponent::Init();
}

void CeilingSensorComponent::Update()
{
	SensorLogicalComponent::Init();
}

void CeilingSensorComponent::Render()
{
	SensorLogicalComponent::Render();
}

void CeilingSensorComponent::Term()
{
	SensorLogicalComponent::Term();
}

void CeilingSensorComponent::Reset()
{
	SensorLogicalComponent::Reset();
}
