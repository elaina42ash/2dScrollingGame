#pragma once
#include "ExecutorComponent.h"
#include "Component/Common/ExecutorComponent/Interface/IPhysicsComponent.h"
#pragma warning(push)
#pragma warning(disable:4250)
class PhysicsComponent : public ExecutorComponent, public IPhysicsComponent
{
protected:
	// 速度
	Lib::Math::Vector2f velocity_ = { 0.0f,0.0f };

	float acceleration_ = 50.0f;

	float maxSpeed_ = 300.0f;

	float gravityScale_ = 5.0f;

	float maxGravity_ = -1200.0f;

	float frictionCoefficient_ = 0.82f;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	Lib::Math::Vector2f GetVelocity() const override final;

protected:
	PhysicsComponent(bool _isActive, float _acceleration, float _maxSpeed, float _gravityScale, float _maxGravity, float _frictionCoefficient, IMessenger* _messenger);

	PhysicsComponent(float _acceleration, float _maxSpeed, float _gravityScale,
		float _maxGravity, float _frictionCoefficient, IMessenger* _messenger);

	PhysicsComponent(bool _isActive, IMessenger* _messenger);

	explicit PhysicsComponent(IMessenger* _messenger);

	void Reset() override;

	void ApplyFrictionToVelocity();

	void ApplyGravityToVelocity();

	void ApplyAccelerationToVelocity();

	void ApplyInputToVelocity(const Lib::Math::Vector2f& _velocityInput);

	void SetVelocity(const Lib::Math::Vector2f& _newVelocity);

public:
	void ClearVerticalVelocity() override;
};


#pragma warning(pop)
