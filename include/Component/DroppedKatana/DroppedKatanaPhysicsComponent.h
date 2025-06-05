#pragma once
#include "Inject.h"
#include "Component/Common/ExecutorComponent/Class/PhysicsComponent.h"
#include "GameObject/DroppedObject/IDroppedObjectView.h"
#include "Player/IPlayerView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class DroppedKatanaPhysicsComponent : public PhysicsComponent
{
private:
	Inject<IDroppedObjectView> droppedObjectView_;

	bool isGravityEnabled_ = true;

	bool isFrictionEnabled_ = true;


	static constexpr float ACCELERATION_DEFAULT = 50.0f;

	static constexpr float MAX_SPEED_DEFAULT = 300.0f;

	static constexpr float GRAVITY_SCALE_DEFAULT = 5.0f;

	static constexpr float MAX_GRAVITY_DEFAULT = -1200.0f;

	static constexpr float FRICTION_COEFFICIENT_DEFAULT = 0.82f;

public:
	DroppedKatanaPhysicsComponent(bool _isActive, float _acceleration, float _maxSpeed, float _gravityScale,
		float _maxGravity, float _frictionCoefficient, IMessenger* _messenger,
		IDroppedObjectView* _droppedObjectView);

	DroppedKatanaPhysicsComponent(float _acceleration, float _maxSpeed, float _gravityScale, float _maxGravity,
		float _frictionCoefficient, IMessenger* _messenger, IDroppedObjectView* _droppedObjectView);

	DroppedKatanaPhysicsComponent(bool _isActive, IMessenger* _messenger,
		IDroppedObjectView* _droppedObjectView);

	DroppedKatanaPhysicsComponent(IMessenger* _messenger, IDroppedObjectView* _droppedObjectView);

	void Init() override;

	void Render() override;

	void Term() override;

	void Update() override;

protected:
	void Reset() override;

public:
	void HandleMessage(const IEventMessage& _msg) override;
};
#pragma warning(pop)
