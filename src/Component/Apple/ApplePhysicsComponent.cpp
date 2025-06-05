#include "Component/Apple/ApplePhysicsComponent.h"


ApplePhysicsComponent::ApplePhysicsComponent(bool _isActive, float _acceleration, float _maxSpeed,
	float _gravityScale, float _maxGravity, float _frictionCoefficient, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(
		_isActive, _acceleration, _maxSpeed, _gravityScale, _maxGravity, _frictionCoefficient, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

ApplePhysicsComponent::ApplePhysicsComponent(float _acceleration, float _maxSpeed, float _gravityScale,
	float _maxGravity, float _frictionCoefficient, IMessenger* _messenger, IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_acceleration, _maxSpeed, _gravityScale, _maxGravity, _frictionCoefficient, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

ApplePhysicsComponent::ApplePhysicsComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

ApplePhysicsComponent::ApplePhysicsComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void ApplePhysicsComponent::Init()
{
	PhysicsComponent::Init();

	acceleration_ = ACCELERATION_DEFAULT;

	maxSpeed_ = MAX_SPEED_DEFAULT;

	gravityScale_ = GRAVITY_SCALE_DEFAULT;

	maxGravity_ = MAX_GRAVITY_DEFAULT;

	frictionCoefficient_ = FRICTION_COEFFICIENT_DEFAULT;
}

void ApplePhysicsComponent::Render()
{
	PhysicsComponent::Render();
}

void ApplePhysicsComponent::Term()
{
	PhysicsComponent::Term();
}

void ApplePhysicsComponent::Update()
{
	PhysicsComponent::Update();


	if (isGravityEnabled_)
		ApplyGravityToVelocity();

	if (isFrictionEnabled_)
		ApplyFrictionToVelocity();


	Reset();
}

void ApplePhysicsComponent::Reset()
{
	PhysicsComponent::Reset();
}

void ApplePhysicsComponent::HandleMessage(const IEventMessage& _msg)
{

}
