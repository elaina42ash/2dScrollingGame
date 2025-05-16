#pragma once
#include "Inject.h"
#include "Component/Common/ExecutorComponent/Class/PhysicsComponent.h"
#include "Player/IPlayerView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class PlayerPhysicsComponent : public PhysicsComponent
{
private:
	Inject<IPlayerView> playerView_;

	bool isGravityEnabled_ = true;

	bool isFrictionEnabled_ = true;


	static constexpr float ACCELERATION_DEFAULT = 50.0f;

	static constexpr float MAX_SPEED_DEFAULT = 300.0f;

	static constexpr float GRAVITY_SCALE_DEFAULT = 5.0f;

	static constexpr float MAX_GRAVITY_DEFAULT = -1200.0f;

	static constexpr float FRICTION_COEFFICIENT_DEFAULT = 0.82f;

public:
	PlayerPhysicsComponent(bool _isActive, float _acceleration, float _maxSpeed, float _gravityScale, float _maxGravity, float _frictionCoefficient, IPlayerView* playerView_,IMessenger* _messenger);

	PlayerPhysicsComponent(float _acceleration, float _maxSpeed, float _gravityScale, float _maxGravity,
		float _frictionCoefficient, IPlayerView* playerView_, IMessenger* _messenger);

	explicit PlayerPhysicsComponent(bool _isActive, IPlayerView* playerView_, IMessenger* _messenger);

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
