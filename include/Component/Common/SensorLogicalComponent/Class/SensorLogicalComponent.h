#pragma once
#include "Inject.h"
#include "Component/Common/Component.h"
#include "Event/IMessenger.h"

class SensorLogicalComponent : public Component
{
public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	SensorLogicalComponent(bool _isActive, IMessenger* _messenger);

	explicit SensorLogicalComponent(IMessenger* _messenger);

	void Reset() override;
};
