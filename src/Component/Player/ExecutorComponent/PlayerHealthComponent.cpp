#include "Component/Player/ExecutorComponent/Class/PlayerHealthComponent.h"
#include "Component/Common/ExecutorComponent/Class/HealthComponent.h"
#include "Event/Message/SemanticMsg/StartHurtSemMsg.h"
#include "Event/Message/StateMsg/SetIsDeadConditionMsg.h"
#include "Fwk/Framework.h"

PlayerHealthComponent::PlayerHealthComponent(bool _isActive, IMessenger* _messenger): HealthComponent(_isActive, _messenger)
{

}

void PlayerHealthComponent::Init()
{
	HealthComponent::Init();

	SetMaxHp(10);
	SetHp(10);
}

void PlayerHealthComponent::Update()
{
	HealthComponent::Update();

	Reset();
}

void PlayerHealthComponent::Render()
{
	HealthComponent::Render();
}

void PlayerHealthComponent::Term()
{
	HealthComponent::Term();
}

void PlayerHealthComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartHurtSemMsg* startHurtSemMsg = TypeidSystem::SafeCast<StartHurtSemMsg>(&_msg);

	if (startHurtSemMsg)
	{
		int incomingDamage = startHurtSemMsg->GetIncomingDamage();
		AddTask([=]()->void
			{
				TakeDamage(incomingDamage);
			});
	}
}

void PlayerHealthComponent::TakeDamage(int _incomingDamage)
{
	SetHp(GetHp() - _incomingDamage);
	if (IsDead())
	{
		SetIsDeadConditionMsg msg(true);
		SendMsg(msg);
	}

	DebugLog("player take damage:"+ to_string(_incomingDamage) +" , "+"HP now : "+to_string(GetHp()));
}

void PlayerHealthComponent::Reset()
{
	HealthComponent::Reset();
}
