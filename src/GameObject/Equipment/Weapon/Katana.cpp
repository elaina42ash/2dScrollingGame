#include "GameObject/Equipment/Weapon/Katana.h"
#include "Component/Katana/ExecutorComponent/KatanaAnimationComponent.h"
#include "Component/Katana/ExecutorComponent/KatanaSoundComponent.h"
#include "Component/Katana/ExecutorComponent/KatanaTransformComponent.h"
#include "Component/Katana/SensorLogicalComponent/Class/KatanaCollisionComponent.h"
#include "Component/Sword/ExecutorComponent/Class/SwordAnimationComponent.h"
#include "Component/Sword/ExecutorComponent/Class/SwordSoundComponent.h"
#include "Component/Sword/ExecutorComponent/Class/SwordTransformComponent.h"
#include "Component/Sword/SensorLogicalComponent/Class/SwordCollisionComponent.h"
#include "Event/Message/AnimationMsg/KatanaAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/KatanaAnimationKeyframeMsg.h"



Katana::Katana():Weapon(nullptr)
{
	InitializeKatanaComponents();
}

Katana::Katana(IEquipOwnerView* _equipOwnerView): Weapon(_equipOwnerView)
{
	InitializeKatanaComponents();
}

Katana::~Katana()
{

	if (transformComponent_)
	{
		delete transformComponent_;
		transformComponent_ = nullptr;
	}

	if (collisionComponent_)
	{
		delete collisionComponent_;
		collisionComponent_ = nullptr;
	}

	if (animationComponent_)
	{
		delete animationComponent_;
		animationComponent_ = nullptr;
	}

	if (soundComponent_)
	{
		delete soundComponent_;
		soundComponent_ = nullptr;
	}
}

void Katana::Init()
{
	Weapon::Init();

	Subscribe(TypeidSystem::GetTypeID<KatanaAnimationCompletedMsg>(), this);

	Subscribe(TypeidSystem::GetTypeID<KatanaAnimationKeyframeMsg>(), collisionComponent_);
	Subscribe(TypeidSystem::GetTypeID<KatanaAnimationBeginMsg>(), collisionComponent_);
	Subscribe(TypeidSystem::GetTypeID<KatanaAnimationCompletedMsg>(), collisionComponent_);

	Subscribe(TypeidSystem::GetTypeID<KatanaAnimationBeginMsg>(), soundComponent_);
}

void Katana::Update()
{
	Weapon::Update();
}

void Katana::Render()
{
	Weapon::Render();
}

void Katana::Term()
{
	Weapon::Term();
}

void Katana::Attack()
{
	mode_ = WeaponMode::ATTACKING;

	if (transformComponent_)
		transformComponent_->Enable();

	if (collisionComponent_)
		collisionComponent_->Enable();

	if (soundComponent_)
		soundComponent_->Enable();

}

void Katana::EndAttack()
{
	mode_ = WeaponMode::EQUIPPED;
		
	if (transformComponent_)
		transformComponent_->Disable();

	if (collisionComponent_)
		collisionComponent_->Disable();

	if (soundComponent_)
		soundComponent_->Disable();
}

void Katana::HandleMessage(const IEventMessage& _msg)
{
	const KatanaAnimationCompletedMsg* katanaAnimationCompletedMsg = TypeidSystem::SafeCast<KatanaAnimationCompletedMsg>(&_msg);

	if (katanaAnimationCompletedMsg)
	{
		EndAttack();
	}
}

void Katana::OnAttackPhaseStarted(int _animationID)
{
	KatanaAnimationBeginMsg katanaAnimationBeginMsg(_animationID);
	SendMsg(katanaAnimationBeginMsg);
}

void Katana::OnAttackKeyframe(int _animationID, int frameIndex)
{
	KatanaAnimationKeyframeMsg katanaAnimationKeyframeMsg(_animationID, frameIndex);
	SendMsg(katanaAnimationKeyframeMsg);
}

void Katana::OnAttackCompleted(int _animationID)
{
	KatanaAnimationCompletedMsg katanaAnimationCompletedMsg(_animationID);
	SendMsg(katanaAnimationCompletedMsg);
}

void Katana::InitializeKatanaComponents()
{
	transformComponent_ = new KatanaTransformComponent(false, this, equipOwnerView_.Injected(), AccessMessenger());
	AddComponent<ITransformComponent>(transformComponent_);
	collisionComponent_ = new KatanaCollisionComponent(false, AccessMessenger(), this);
	AddComponent<ICollisionComponent>(collisionComponent_);
	animationComponent_ = new KatanaAnimationComponent(false, AccessMessenger(), this);
	AddComponent<IAnimationComponent>(animationComponent_);
	soundComponent_ = new KatanaSoundComponent(false, this, AccessMessenger());
	AddComponent<ISoundComponent>(soundComponent_);
}
