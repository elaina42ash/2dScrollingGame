#pragma once
#include "SensorLogicalComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/IGroundSensorComponent.h"
#include "Sensor/ILineSensor.h"
#pragma warning(push)
#pragma warning(disable:4250)
class GroundSensorComponent : public SensorLogicalComponent,public IGroundSensorComponent
{
protected:
	ILineSensor* lineSensor_;

	bool isGrounded_ = false;
protected:
	GroundSensorComponent(bool _isActive, IMessenger* _messenger, const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position);

	explicit GroundSensorComponent(IMessenger* _messenger, const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position);

	GroundSensorComponent(bool _isActive, IMessenger* _messenger);

	GroundSensorComponent(IMessenger* _messenger);

	~GroundSensorComponent() override;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void SetDetectedResult(bool _result);

	void Reset() override;
public:
	bool Detected() override final;

private:
	void ResetDetectedResult();
};
#pragma warning(pop)