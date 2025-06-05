#include "Component/DroppedKatana/DroppedKatanaPhysicsComponent.h"


DroppedKatanaPhysicsComponent::DroppedKatanaPhysicsComponent(bool _isActive, float _acceleration, float _maxSpeed,
	float _gravityScale, float _maxGravity, float _frictionCoefficient, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(
		_isActive, _acceleration, _maxSpeed, _gravityScale, _maxGravity, _frictionCoefficient, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedKatanaPhysicsComponent::DroppedKatanaPhysicsComponent(float _acceleration, float _maxSpeed, float _gravityScale,
	float _maxGravity, float _frictionCoefficient, IMessenger* _messenger, IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_acceleration, _maxSpeed, _gravityScale, _maxGravity, _frictionCoefficient, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedKatanaPhysicsComponent::DroppedKatanaPhysicsComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedKatanaPhysicsComponent::DroppedKatanaPhysicsComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : PhysicsComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void DroppedKatanaPhysicsComponent::Init()
{
	PhysicsComponent::Init();

	acceleration_ = ACCELERATION_DEFAULT;

	maxSpeed_ = MAX_SPEED_DEFAULT;

	gravityScale_ = GRAVITY_SCALE_DEFAULT;

	maxGravity_ = MAX_GRAVITY_DEFAULT;

	frictionCoefficient_ = FRICTION_COEFFICIENT_DEFAULT;
}

void DroppedKatanaPhysicsComponent::Render()
{
	PhysicsComponent::Render();
}

void DroppedKatanaPhysicsComponent::Term()
{
	PhysicsComponent::Term();
}

void DroppedKatanaPhysicsComponent::Update()
{
	PhysicsComponent::Update();


	if (isGravityEnabled_)
		ApplyGravityToVelocity();

	if (isFrictionEnabled_)
		ApplyFrictionToVelocity();


	Reset();
}

void DroppedKatanaPhysicsComponent::Reset()
{
	PhysicsComponent::Reset();
}

void DroppedKatanaPhysicsComponent::HandleMessage(const IEventMessage& _msg)
{

}
