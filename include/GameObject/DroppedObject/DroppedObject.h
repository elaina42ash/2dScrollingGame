#pragma once
#include "IDroppedObjectView.h"
#include "Component/Common/ExecutorComponent/Interface/IAnimationComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IMovementComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IPhysicsComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ITransformComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ITileMapSensorComponent.h"
#include "GameObject/GameObject.h"


class DroppedObject : public GameObject,public IDroppedObjectView
{
protected:
	ITransformComponent* transformComponent_;
	IAnimationComponent* animationComponent_;
	ICollisionComponent* collisionComponent_;
	IPhysicsComponent* physicsComponent_;
	IMovementComponent* movementComponent_;
	ITileMapSensorComponent* tileMapSensorComponent_;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	Lib::Math::Vector2f GetVelocity() const override final;

	float GetVelocityX() const override final;

	float GetVelocityY() const override final;

	float GetPositionX() const override final;

	float GetPositionY() const override final;

	float GetTileSize() const override final;

	Lib::Math::Vector2f GetPosition() const override final;

	bool IsInsideWallRect(Lib::Math::Vector2f _position, float _width, float _height) const override final;

	bool IsInsideWallCircle(Lib::Math::Vector2f _position, float _radius) const override final;

protected:
	DroppedObject() = default;
};
