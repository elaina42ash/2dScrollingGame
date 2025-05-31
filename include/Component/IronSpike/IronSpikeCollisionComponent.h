#pragma once
#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"

#pragma warning(push)
#pragma warning(disable:4250)
class IronSpikeCollisionComponent : public CollisionComponent
{
public:
	IronSpikeCollisionComponent(bool _isActive, IMessenger* _messenger);

	explicit IronSpikeCollisionComponent(IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)
