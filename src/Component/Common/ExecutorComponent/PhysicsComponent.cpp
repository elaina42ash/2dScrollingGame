#include "Component/Common/ExecutorComponent/Class/PhysicsComponent.h"
#include "GameMath.h"
#include "Fwk/Framework.h"

PhysicsComponent::PhysicsComponent(bool _isActive, float _acceleration, float _maxSpeed, float _gravityScale,
	float _maxGravity, float _frictionCoefficient, IMessenger* _messenger) : ExecutorComponent(_isActive, _messenger),
	acceleration_(_acceleration),
	maxSpeed_(_maxSpeed),
	gravityScale_(_gravityScale),
	maxGravity_(_maxGravity),
	frictionCoefficient_(_frictionCoefficient)
{
}

PhysicsComponent::PhysicsComponent(float _acceleration, float _maxSpeed, float _gravityScale, float _maxGravity,
	float _frictionCoefficient, IMessenger* _messenger) :ExecutorComponent(_messenger), acceleration_(_acceleration),
	maxSpeed_(_maxSpeed),
	gravityScale_(_gravityScale),
	maxGravity_(_maxGravity),
	frictionCoefficient_(_frictionCoefficient)
{
}

PhysicsComponent::PhysicsComponent(bool _isActive, IMessenger* _messenger) : ExecutorComponent(_isActive, _messenger)
{
}

void PhysicsComponent::Init()
{
	ExecutorComponent::Init();
}

void PhysicsComponent::Update()
{
	ExecutorComponent::Update();

}

void PhysicsComponent::Render()
{
	ExecutorComponent::Render();
}

void PhysicsComponent::Term()
{
	ExecutorComponent::Term();
}

Lib::Math::Vector2f PhysicsComponent::GetVelocity() const
{
	return velocity_;
}

PhysicsComponent::PhysicsComponent(IMessenger* _messenger) :ExecutorComponent(_messenger)
{

}

void PhysicsComponent::Reset()
{
	ExecutorComponent::Reset();
}

void PhysicsComponent::ApplyFrictionToVelocity()
{
	
	float dt = Time_I->GetDeltaTime();

	float damping = powf(frictionCoefficient_, dt * 60.0f);

	velocity_.x *= damping;

	if (fabsf(velocity_.x) < 0.1f)
	{
		velocity_.x = 0.0f;
	}
}

void PhysicsComponent::ApplyGravityToVelocity()
{
	// このフレームでの重力加速量。
	float gravityFrame = -9.8f * Time_I->GetDeltaTime() * gravityScale_;

	// このフレームでの最大重力
	float maxGravityFrame = maxGravity_ * Time_I->GetDeltaTime();

	// 重力の計算
	velocity_.y += gravityFrame;
	if (velocity_.y < maxGravityFrame)
	{
		velocity_.y = maxGravityFrame;
	}
}

void PhysicsComponent::ApplyAccelerationToVelocity()
{
	// このフレームでの移動量
	float accelerationFrame = acceleration_ * Time_I->GetDeltaTime();
	// このフレームでの最大移動量
	float maxSpeedFrame = maxSpeed_ * Time_I->GetDeltaTime();

	// 速度ベクトルに、加速分のベクトルを足しこむ
	velocity_.x += velocity_.x * accelerationFrame;
	// 速さが上限を超えないようにする
	if (fabsf(velocity_.x) > maxSpeedFrame)
	{
		velocity_.x = maxSpeedFrame * (velocity_.x) / (fabsf(velocity_.x));
	}
}

void PhysicsComponent::ApplyInputToVelocity(const Lib::Math::Vector2f& _velocityInput)
{
	if (!GameMath::FloatIsZero(_velocityInput.x))
		velocity_.x += _velocityInput.x;


	if (!GameMath::FloatIsZero(_velocityInput.y))
		velocity_.y += _velocityInput.y;

}

void PhysicsComponent::SetVelocity(const Vector2f& _newVelocity)
{
	velocity_ = _newVelocity;
}

void PhysicsComponent::ClearVerticalVelocity()
{
	velocity_.y = 0;
}
