#pragma once
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "GameObject/StaticObject.h"

class IronSpike : public StaticObject 
{
public:
	IronSpike();

	~IronSpike();

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

	Lib::Math::Vector2f GetPosition() const override;
};
