#pragma once
#include "SensorLogicalComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICeilingSensorComponent.h"
#include "Sensor/ILineSensor.h"

#pragma warning(push)
#pragma warning(disable:4250)
class CeilingSensorComponent : public SensorLogicalComponent , public ICeilingSensorComponent
{
private:
	ILineSensor* lineSensor_;

protected:
	CeilingSensorComponent(bool _isActive, IMessenger* _messenger, const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position);

	explicit CeilingSensorComponent(IMessenger* _messenger, const Lib::Math::Vector2f& _rayVec, const Lib::Math::Vector2f& _position);

public:
	~CeilingSensorComponent() override;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	void Reset() override;
};
#pragma warning(pop)