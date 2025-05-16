#include "Component/Player/ExecutorComponent/Class/PlayerCombatStatusComponent.h"
#include "Component/Common/ExecutorComponent/Class/CombatStatusComponent.h"
#include "Event/Message/SemanticMsg/EndDashSemMsg.h"
#include "Event/Message/SemanticMsg/EndKnockBackSemMsg.h"
#include "Event/Message/SemanticMsg/StartDashSemMsg.h"


PlayerCombatStatusComponent::PlayerCombatStatusComponent(bool _isActive, IMessenger* _messenger) :CombatStatusComponent(_isActive, _messenger)
{
}

PlayerCombatStatusComponent::PlayerCombatStatusComponent(IMessenger* _messenger) :CombatStatusComponent(_messenger)
{

}

void PlayerCombatStatusComponent::Init()
{
	CombatStatusComponent::Init();

	invincibilityFrames_ = 0;
}

void PlayerCombatStatusComponent::Update()
{
	CombatStatusComponent::Update();

	Reset();
}

void PlayerCombatStatusComponent::Render()
{
	CombatStatusComponent::Render();
}

void PlayerCombatStatusComponent::Term()
{
	CombatStatusComponent::Term();
}

void PlayerCombatStatusComponent::HandleMessage(const IEventMessage& _msg)
{
	const EndKnockBackSemMsg* endKnockBackSemMsg = TypeidSystem::SafeCast<EndKnockBackSemMsg>(&_msg);
	const StartDashSemMsg* startDashSemMsg = TypeidSystem::SafeCast<StartDashSemMsg>(&_msg);
	const EndDashSemMsg* endDashSemMsg = TypeidSystem::SafeCast<EndDashSemMsg>(&_msg);

	if (endKnockBackSemMsg)
	{
		int invincibilityFrames = 60;
		AddTask([=]()->void
			{
				this->invincibilityFrames_ = invincibilityFrames;
			});
	}

	if (startDashSemMsg)
	{
		int invincibilityFrames = INT_MAX;
		AddTask([=]()->void
			{
				this->invincibilityFrames_ = invincibilityFrames;
			});
	}

	if (endDashSemMsg)
	{
		int invincibilityFrames = 0;
		AddTask([=]()->void
			{
				this->invincibilityFrames_ = invincibilityFrames;
			});
	}
}

void PlayerCombatStatusComponent::Reset()
{
	CombatStatusComponent::Reset();
}
