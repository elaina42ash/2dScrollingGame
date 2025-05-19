#include "GameObject/Equipment/Weapon/Katana.h"
#include "Component/Sword/ExecutorComponent/Class/SwordAnimationComponent.h"
#include "Component/Sword/ExecutorComponent/Class/SwordSoundComponent.h"
#include "Component/Sword/ExecutorComponent/Class/SwordTransformComponent.h"
#include "Component/Sword/SensorLogicalComponent/Class/SwordCollisionComponent.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"



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

	Subscribe(TypeidSystem::GetTypeID<SwordAnimationCompletedMsg>(), this);

	Subscribe(TypeidSystem::GetTypeID<SwordAnimationKeyframeMsg>(), collisionComponent_);
	Subscribe(TypeidSystem::GetTypeID<SwordAnimationCompletedMsg>(), collisionComponent_);
	Subscribe(TypeidSystem::GetTypeID<SwordAnimationBeginMsg>(), collisionComponent_);

	Subscribe(TypeidSystem::GetTypeID<SwordAnimationBeginMsg>(), soundComponent_);
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
	const SwordAnimationCompletedMsg* swordAnimationCompletedMsg = TypeidSystem::SafeCast<SwordAnimationCompletedMsg>(&_msg);

	if (swordAnimationCompletedMsg)
	{
		EndAttack();
	}
}

void Katana::OnAttackPhaseStarted(int _animationID)
{
	SwordAnimationBeginMsg swordAnimationBegin(_animationID);
	SendMsg(swordAnimationBegin);
}

void Katana::OnAttackKeyframe(int _animationID, int frameIndex)
{
		
}

void Katana::OnAttackCompleted(int _animationID)
{
	SwordAnimationCompletedMsg swordAnimationCompletedMsg(_animationID);
	SendMsg(swordAnimationCompletedMsg);
}

void Katana::InitializeKatanaComponents()
{
	transformComponent_ = new SwordTransformComponent(false, this, equipOwnerView_.Injected(), AccessMessenger());
	AddComponent<ITransformComponent>(transformComponent_);
	collisionComponent_ = new SwordCollisionComponent(false, AccessMessenger(), this);
	AddComponent<ICollisionComponent>(collisionComponent_);
	animationComponent_ = new SwordAnimationComponent(false, AccessMessenger(), this);
	AddComponent<IAnimationComponent>(animationComponent_);
	soundComponent_ = new SwordSoundComponent(false, this, AccessMessenger());
	AddComponent<ISoundComponent>(soundComponent_);
}
