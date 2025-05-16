#include "Component/Common/SensorLogicalComponent/Class/GroundSensorComponent.h"
#include "Sensor/LineSensor.h"

GroundSensorComponent::GroundSensorComponent(bool _isActive, IMessenger* _messenger, const Lib::Math::Vector2f& _rayVec,
                                             const Lib::Math::Vector2f& _position): SensorLogicalComponent(_isActive, _messenger)
{
	lineSensor_ = new LineSensor(_rayVec, _position);
}

GroundSensorComponent::GroundSensorComponent(IMessenger* _messenger, const Lib::Math::Vector2f& _rayVec,
	const Lib::Math::Vector2f& _position): SensorLogicalComponent(_messenger)
{
	lineSensor_ = new LineSensor(_rayVec, _position);
}

GroundSensorComponent::GroundSensorComponent(bool _isActive, IMessenger* _messenger): SensorLogicalComponent(_isActive, _messenger)
{
	lineSensor_ = new LineSensor();
}

GroundSensorComponent::GroundSensorComponent(IMessenger* _messenger): SensorLogicalComponent(_messenger)
{
	lineSensor_ = new LineSensor();
}

GroundSensorComponent::~GroundSensorComponent()
{
	if (lineSensor_)
	{
		delete lineSensor_;
		lineSensor_ = nullptr;
	}
}

void GroundSensorComponent::Init()
{
	SensorLogicalComponent::Init();
}

void GroundSensorComponent::Update()
{
	SensorLogicalComponent::Update();
	ResetDetectedResult();
}

void GroundSensorComponent::Render()
{
	SensorLogicalComponent::Render();
}

void GroundSensorComponent::Term()
{
	SensorLogicalComponent::Term();
}

void GroundSensorComponent::SetDetectedResult(bool _result)
{
	isGrounded_ = _result;
}

bool GroundSensorComponent::Detected()
{
	return isGrounded_;
}

void GroundSensorComponent::ResetDetectedResult()
{
	isGrounded_ = false;
}

void GroundSensorComponent::Reset()
{
	SensorLogicalComponent::Reset();
}
