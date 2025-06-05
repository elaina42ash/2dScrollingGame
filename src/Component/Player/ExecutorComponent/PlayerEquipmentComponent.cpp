#include "Component/Player/ExecutorComponent/Class/PlayerEquipmentComponent.h"

#include "Event/Message/AnimationMsg/KatanaAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationKeyframeMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"
#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "Event/Message/SemanticMsg/StartDropWeaponSemMsg.h"
#include "Event/Message/SemanticMsg/StartSwitchWeaponSemMsg.h"
#include "GameObject/Equipment/Weapon/Katana.h"

PlayerEquipmentComponent::PlayerEquipmentComponent(bool _isActive, IPlayerView* playerView_, IEquipOwnerView* _equipOwnerView, IMessenger* _messenger) : EquipmentComponent(_isActive, _equipOwnerView, _messenger), playerView_(playerView_)
{
}

void PlayerEquipmentComponent::Init()
{
	EquipmentComponent::Init();

}

void PlayerEquipmentComponent::Update()
{
	EquipmentComponent::Update();

	Reset();
}

void PlayerEquipmentComponent::Render()
{
	EquipmentComponent::Render();
}

void PlayerEquipmentComponent::Term()
{
	EquipmentComponent::Term();
}

void PlayerEquipmentComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartAttackSemMsg* startAttackSemMsg = TypeidSystem::SafeCast<StartAttackSemMsg>(&_msg);
	const SwordAnimationBeginMsg* swordAnimationBegin = TypeidSystem::SafeCast<SwordAnimationBeginMsg>(&_msg);
	const SwordAnimationKeyframeMsg* swordAnimationKeyframeMsg = TypeidSystem::SafeCast<SwordAnimationKeyframeMsg>(&_msg);
	const SwordAnimationCompletedMsg* swordAnimationCompletedMsg = TypeidSystem::SafeCast<SwordAnimationCompletedMsg>(&_msg);
	const KatanaAnimationBeginMsg* katanaAnimationBeginMsg = TypeidSystem::SafeCast<KatanaAnimationBeginMsg>(&_msg);
	const KatanaAnimationKeyframeMsg* katanaAnimationKeyframeMsg = TypeidSystem::SafeCast<KatanaAnimationKeyframeMsg>(&_msg);
	const KatanaAnimationCompletedMsg* katanaAnimationCompletedMsg = TypeidSystem::SafeCast<KatanaAnimationCompletedMsg>(&_msg);
	const StartSwitchWeaponSemMsg* switchWeaponSemMsg = TypeidSystem::SafeCast<StartSwitchWeaponSemMsg>(&_msg);
	const StartDropWeaponSemMsg* startDropWeaponSemMsg = TypeidSystem::SafeCast<StartDropWeaponSemMsg>(&_msg);

	if (startAttackSemMsg)
	{
		AddTask([=]()->void
			{
				this->Attack();
			});

	}

	if (swordAnimationBegin)
	{
		if (std::dynamic_pointer_cast<Sword>(activeWeapon))
			activeWeapon->OnAttackPhaseStarted(swordAnimationBegin->GetAnimationID());
	}

	if (swordAnimationKeyframeMsg)
	{
		if (std::dynamic_pointer_cast<Sword>(activeWeapon))
			activeWeapon->OnAttackKeyframe(swordAnimationKeyframeMsg->GetAnimationID(), swordAnimationKeyframeMsg->GetKeyFrameIndex());
	}

	if (swordAnimationCompletedMsg)
	{
		if (std::dynamic_pointer_cast<Sword>(activeWeapon))
			activeWeapon->OnAttackCompleted(swordAnimationCompletedMsg->GetAnimationID());
	}

	if (katanaAnimationBeginMsg)
	{
		if (std::dynamic_pointer_cast<Katana>(activeWeapon))
			activeWeapon->OnAttackPhaseStarted(katanaAnimationBeginMsg->GetAnimationID());
	}

	if (katanaAnimationKeyframeMsg)
	{
		if (std::dynamic_pointer_cast<Katana>(activeWeapon))
			activeWeapon->OnAttackKeyframe(katanaAnimationKeyframeMsg->GetAnimationID(), katanaAnimationKeyframeMsg->GetKeyFrameIndex());
	}

	if (katanaAnimationCompletedMsg)
	{
		if (std::dynamic_pointer_cast<Katana>(activeWeapon))
			activeWeapon->OnAttackCompleted(katanaAnimationCompletedMsg->GetAnimationID());
	}

	if (switchWeaponSemMsg)
	{
		AddTask([=]()->void
			{
				this->SwitchToNextWeapon();
			});
	}

	if (startDropWeaponSemMsg)
	{
		AddTask([=]()->void
			{
				this->DropWeapon();
			});
	}
}

void PlayerEquipmentComponent::Reset()
{
	EquipmentComponent::Reset();
}

void PlayerEquipmentComponent::Attack()
{
	if (activeWeapon == nullptr || activeSlotID_ == static_cast<int>(EquipmentType::NONE))
		return;
	activeWeapon->Attack();
}
