#pragma once
#include "ExecutorComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IMovementComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IPhysicsComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ITileMapSensorComponent.h"
#include "GameObjectMng/IEnvironmentQuery.h"
#pragma warning(push)
#pragma warning(disable:4250)
class MovementComponent : public ExecutorComponent, public IMovementComponent
{
protected:
	Inject<ITransformComponent> transformComponent_;
	Inject<ITileMapSensorComponent> tileMapSensorComponent_;
	Inject<ICollisionComponent> collisionComponent_;
	Inject<IPhysicsComponent> physicsComponent_;

private:
	virtual void Move(const Lib::Math::Vector2f& _velocity) = 0;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;


protected:
	explicit MovementComponent(bool _isActive, IMessenger* _messenger);

	MovementComponent(IMessenger* _messenger);

	void Reset() override;
};
#pragma warning(pop)