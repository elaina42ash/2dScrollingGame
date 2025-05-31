#pragma once
#include "GameObject.h"
#include "Component/Common/ExecutorComponent/Interface/IAnimationComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"

class StaticObject : public GameObject
{
private:
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
