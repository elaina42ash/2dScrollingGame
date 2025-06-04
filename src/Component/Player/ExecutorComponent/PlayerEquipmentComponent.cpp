#include "Component/Player/ExecutorComponent/Class/PlayerEquipmentComponent.h"

#include "Event/Message/AnimationMsg/KatanaAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationKeyframeMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"
#include "Event/Message/SemanticMsg/StartAttackSemMsg.h"
#include "Event/Message/SemanticMsg/StartSwitchWeaponSemMsg.h"
#include "GameObject/Equipment/Weapon/Katana.h"
#include "GameObject/Equipment/Weapon/Sword.h"

PlayerEquipmentComponent::PlayerEquipmentComponent(bool _isActive, IPlayerView* playerView_, IEquipOwnerView* _equipOwnerView, IMessenger* _messenger) : EquipmentComponent(_isActive, _equipOwnerView, _messenger), playerView_(playerView_)
{
}

void PlayerEquipmentComponent::Init()
{
	EquipmentComponent::Init();

	//TODO:hard coding
	std::shared_ptr<Sword> sword = std::make_shared<Sword>(equipOwnerView_.Injected());
	std::shared_ptr<Katana> katana = std::make_shared<Katana>(equipOwnerView_.Injected());

	sword->Init();
	katana->Init();
	Equip(static_cast<int>(EquipmentSlotType::WEAPON_1), sword);
	Equip(static_cast<int>(EquipmentSlotType::WEAPON_2), sword);

	SwitchWeapon(static_cast<int>(EquipmentSlotType::WEAPON_1));

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

	if (startAttackSemMsg)
	{
		AddTask([=]()->void
			{
				this->Attack();
			});

	}

	if (swordAnimationBegin)
	{
		if (activeWeaponID_ == static_cast<int>(EquipmentType::SWORD))
			activeWeapon->OnAttackPhaseStarted(swordAnimationBegin->GetAnimationID());
	}

	if (swordAnimationKeyframeMsg)
	{
		if (activeWeaponID_ == static_cast<int>(EquipmentType::SWORD))
			activeWeapon->OnAttackKeyframe(swordAnimationKeyframeMsg->GetAnimationID(), swordAnimationKeyframeMsg->GetKeyFrameIndex());
	}

	if (swordAnimationCompletedMsg)
	{
		if (activeWeaponID_ == static_cast<int>(EquipmentType::SWORD))
			activeWeapon->OnAttackCompleted(swordAnimationCompletedMsg->GetAnimationID());
	}

	if (katanaAnimationBeginMsg)
	{
		if (activeWeaponID_ == static_cast<int>(EquipmentType::KATANA))
			activeWeapon->OnAttackPhaseStarted(katanaAnimationBeginMsg->GetAnimationID());
	}

	if (katanaAnimationKeyframeMsg)
	{
		if (activeWeaponID_ == static_cast<int>(EquipmentType::KATANA))
			activeWeapon->OnAttackKeyframe(katanaAnimationKeyframeMsg->GetAnimationID(), katanaAnimationKeyframeMsg->GetKeyFrameIndex());
	}

	if (katanaAnimationCompletedMsg)
	{
		if (activeWeaponID_ == static_cast<int>(EquipmentType::KATANA))
			activeWeapon->OnAttackCompleted(katanaAnimationCompletedMsg->GetAnimationID());
	}

	if (switchWeaponSemMsg)
	{
		AddTask([=]()->void
			{
				this->SwitchToNextWeapon();
			});
	}
}

void PlayerEquipmentComponent::Reset()
{
	EquipmentComponent::Reset();
}

void PlayerEquipmentComponent::Attack()
{
	if (activeWeapon == nullptr || activeWeaponID_ == static_cast<int>(EquipmentType::NONE))
		return;
	activeWeapon->Attack();
}
