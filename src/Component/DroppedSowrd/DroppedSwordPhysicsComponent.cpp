#include "Component/DroppedSword/DroppedSwordPhysicsComponent.h"


DroppedSwordPhysicsComponent::DroppedSwordPhysicsComponent(bool _isActive, float _acceleration, float _maxSpeed,
	float _gravityScale, float _maxGravity, float _frictionCoefficient, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(
		_isActive, _acceleration, _maxSpeed, _gravityScale, _maxGravity, _frictionCoefficient, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedSwordPhysicsComponent::DroppedSwordPhysicsComponent(float _acceleration, float _maxSpeed, float _gravityScale,
	float _maxGravity, float _frictionCoefficient, IMessenger* _messenger, IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_acceleration, _maxSpeed, _gravityScale, _maxGravity, _frictionCoefficient, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedSwordPhysicsComponent::DroppedSwordPhysicsComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedSwordPhysicsComponent::DroppedSwordPhysicsComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void DroppedSwordPhysicsComponent::Init()
{
	PhysicsComponent::Init();

	acceleration_ = ACCELERATION_DEFAULT;

	maxSpeed_ = MAX_SPEED_DEFAULT;

	gravityScale_ = GRAVITY_SCALE_DEFAULT;

	maxGravity_ = MAX_GRAVITY_DEFAULT;

	frictionCoefficient_ = FRICTION_COEFFICIENT_DEFAULT;
}

void DroppedSwordPhysicsComponent::Render()
{
	PhysicsComponent::Render();
}

void DroppedSwordPhysicsComponent::Term()
{
	PhysicsComponent::Term();
}

void DroppedSwordPhysicsComponent::Update()
{
	PhysicsComponent::Update();


	if (isGravityEnabled_)
		ApplyGravityToVelocity();

	if (isFrictionEnabled_)
		ApplyFrictionToVelocity();


	Reset();
}

void DroppedSwordPhysicsComponent::Reset()
{
	PhysicsComponent::Reset();
}

void DroppedSwordPhysicsComponent::HandleMessage(const IEventMessage& _msg)
{

}
