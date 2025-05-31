#pragma once
#include "Component/Common/ExecutorComponent/Class/TransformComponent.h"

#pragma warning(push)
#pragma warning(disable:4250)
class IronSpikeTransformComponent : public TransformComponent
{
public:
	IronSpikeTransformComponent(bool _isActive, IMessenger* _messenger);

	explicit IronSpikeTransformComponent(IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)
