#pragma once
#include "GameObject.h"
#include "Component/Common/ExecutorComponent/Interface/IAnimationComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "StaticObject/IStaticObjectView.h"

class StaticObject : public GameObject, public IStaticObjectView
{
protected:
	ITransformComponent* transformComponent_;
	IAnimationComponent* animationComponent_;
	ICollisionComponent* collisionComponent_;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	StaticObject() = default;
};
