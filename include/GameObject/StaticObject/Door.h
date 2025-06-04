#pragma once
#include "IStaticObjectView.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "GameObject/StaticObject.h"

class Door : public StaticObject
{
public:
	Door();

	~Door();

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

	Lib::Math::Vector2f GetPosition() const override;
};
