#include "Component/Player/ExecutorComponent/Class/PlayerTransformComponent.h"
#include "GameMath.h"
#include "Component/Common/ExecutorComponent/Class/TransformComponent.h"
#include "Event/Message/SemanticMsg/StartMoveSemMsg.h"

PlayerTransformComponent::PlayerTransformComponent(bool _isActive, IMessenger* _messenger) : TransformComponent(_isActive, _messenger)
{
}

PlayerTransformComponent::PlayerTransformComponent(IMessenger* _messenger):TransformComponent(_messenger)
{
		
}

void PlayerTransformComponent::Init()
{
	TransformComponent::Init();

	ChangeDirection(Direction::RIGHT);
}

void PlayerTransformComponent::Update()
{
	TransformComponent::Update();

	Reset();
}

void PlayerTransformComponent::Render()
{
	TransformComponent::Render();
}

void PlayerTransformComponent::Term()
{
	TransformComponent::Term();
}

void PlayerTransformComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartMoveSemMsg* startMoveSemMsg = TypeidSystem::SafeCast<StartMoveSemMsg>(&_msg);

	if (startMoveSemMsg)
	{
		Lib::Math::Vector2f moveInput = startMoveSemMsg->GetMoveInput();
		AddTask([=]()->void
			{
				// 向きを更新
				if (!GameMath::FloatIsZero(moveInput.GetLength()))
					ChangeDirection((moveInput.x < 0.0f) ? Direction::LEFT : Direction::RIGHT);
			});
	}


}

void PlayerTransformComponent::Reset()
{
	TransformComponent::Term();
}



