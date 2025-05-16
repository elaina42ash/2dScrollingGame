#include "Component/Player/ExecutorComponent/Class/PlayerPhysicsComponent.h"
#include "Component/Common/ExecutorComponent/Class/PhysicsComponent.h"
#include "Event/Message/SemanticMsg/EndDashSemMsg.h"
#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "Event/Message/SemanticMsg/StartDashSemMsg.h"
#include "Event/Message/SemanticMsg/StartIdleSemMsg.h"
#include "Event/Message/SemanticMsg/StartJumpSemMsg.h"
#include "Event/Message/SemanticMsg/StartKnockBackSemMsg.h"
#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"
#include "Event/Message/SemanticMsg/StopJumpSemMsg.h"
#include "Fwk/Framework.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(bool _isActive, float _acceleration, float _maxSpeed,
	float _gravityScale, float _maxGravity, float _frictionCoefficient, IPlayerView* playerView_, IMessenger* _messenger) : ::PhysicsComponent(_isActive, _acceleration, _maxSpeed, _gravityScale, _maxGravity, _frictionCoefficient, _messenger), playerView_(playerView_)
{
}

PlayerPhysicsComponent::PlayerPhysicsComponent(float _acceleration, float _maxSpeed, float _gravityScale,
	float _maxGravity, float _frictionCoefficient, IPlayerView* playerView_, IMessenger* _messenger) : PhysicsComponent(_acceleration, _maxSpeed, _gravityScale, _maxGravity, _frictionCoefficient, _messenger), playerView_(playerView_)
{
}

PlayerPhysicsComponent::PlayerPhysicsComponent(bool _isActive, IPlayerView* playerView_, IMessenger* _messenger) : PhysicsComponent(_isActive, _messenger), playerView_(playerView_)
{
}

void PlayerPhysicsComponent::Init()
{
	PhysicsComponent::Init();

	acceleration_ = ACCELERATION_DEFAULT;

	maxSpeed_ = MAX_SPEED_DEFAULT;

	gravityScale_ = GRAVITY_SCALE_DEFAULT;

	maxGravity_ = MAX_GRAVITY_DEFAULT;

	frictionCoefficient_ = FRICTION_COEFFICIENT_DEFAULT;
}

void PlayerPhysicsComponent::Render()
{
	PhysicsComponent::Render();
}

void PlayerPhysicsComponent::Term()
{
	PhysicsComponent::Term();
}

void PlayerPhysicsComponent::Update()
{
	PhysicsComponent::Update();


	if (isGravityEnabled_)
		ApplyGravityToVelocity();

	if (isFrictionEnabled_)
		ApplyFrictionToVelocity();


	Reset();
}

void PlayerPhysicsComponent::Reset()
{
	PhysicsComponent::Reset();
}

void PlayerPhysicsComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartMoveSemMsg* startMoveSemMsg = TypeidSystem::SafeCast<StartMoveSemMsg>(&_msg);
	const StartJumpSemMsg* startJumpSemMsg = TypeidSystem::SafeCast<StartJumpSemMsg>(&_msg);
	const StopJumpSemMsg* stopJumpSemMsg = TypeidSystem::SafeCast<StopJumpSemMsg>(&_msg);
	const StartIdleSemMsg* startIdleSemMsg = TypeidSystem::SafeCast<StartIdleSemMsg>(&_msg);
	const StartKnockBackSemMsg* startKnockBackSemMsg = TypeidSystem::SafeCast<StartKnockBackSemMsg>(&_msg);
	const StartAttackSemMsg* startAttackSemMsg = TypeidSystem::SafeCast<StartAttackSemMsg>(&_msg);
	const StartDashSemMsg* startDashSem = TypeidSystem::SafeCast<StartDashSemMsg>(&_msg);
	const EndDashSemMsg* endDashSemMsg = TypeidSystem::SafeCast<EndDashSemMsg>(&_msg);

	if (startMoveSemMsg)
	{
		Vector2f moveInput = startMoveSemMsg->GetMoveInput();
		AddTask([=]()->void
			{
				this->ApplyInputToVelocity(moveInput);
			});
	}

	if (startJumpSemMsg)
	{
		// TODO:hard coding jump power
		Vector2f moveInput = { 0.0f,20.0f };
		AddTask([=]()->void
			{
				if (velocity_.y < 0.0f)
					velocity_.y = 0.0f;
				this->ApplyInputToVelocity(moveInput);
			});
	}

	if (stopJumpSemMsg)
	{
		Vector2f moveInput = { 0.0f,0.0f };

		if (velocity_.y > 0)
		{
			// TODO:hard coding release jump power
			moveInput.y = velocity_.y * 0.5f - velocity_.y;
			AddTask([=]()->void
				{
					this->ApplyInputToVelocity(moveInput);
				});
		}
	}

	if (startIdleSemMsg)
	{
		Vector2f moveInput = { 0.0f,0.0f };
		AddTask([=]()->void
			{
				this->ApplyInputToVelocity(moveInput);
			});
	}

	if (startKnockBackSemMsg)
	{
		if (!playerView_->IsInVincible())
		{
			Vector2f moveInput = { 0.0f,0.0f };

			// 現在の向きに対応する吹き飛び方向
			switch (playerView_->GetDirection())
			{
			case Direction::RIGHT:  moveInput.x = -1.0; break;
			case Direction::LEFT:moveInput.x = 1.0; break;
			default:break;
			}

			float knockBackSpeedFrame = 600.0f * Time_I->GetDeltaTime();

			moveInput.x *= knockBackSpeedFrame;

			ClearTaskQueue();
			AddTask([=]()->void
				{
					this->velocity_ = { 0.0f,0.0f };
					this->ApplyInputToVelocity(moveInput);
				});
		}
	}

	if (startAttackSemMsg)
	{

	}

	if (startDashSem)
	{
		Vector2f newVelocity = { 0.0f,0.0f };
		float dashSpeed = 20.0f;

		switch (playerView_->GetDirection())
		{
		case Direction::RIGHT:newVelocity.x += dashSpeed; break;
		case Direction::LEFT:newVelocity.x += dashSpeed * -1; break;
		default:
			break;
		}

		AddTask([=]()->void
			{
				this->SetVelocity(newVelocity);
				isGravityEnabled_ = false;
				isFrictionEnabled_ = false;
			});
	}

	if (endDashSemMsg)
	{
		AddTask([=]()->void
			{
				isGravityEnabled_ = true;
				isFrictionEnabled_ = true;
			});
	}
}
