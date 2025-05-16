#include "Component/Sword/ExecutorComponent/Class/SwordSoundComponent.h"
#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"
#include "Sound/SoundDef.h"

SwordSoundComponent::SwordSoundComponent(bool _isActive, IWeaponView* _swordView, IMessenger* _messenger) : SoundComponent(_isActive, _messenger), swordView_(_swordView)
{

}

void SwordSoundComponent::Init()
{
	SoundComponent::Init();

	LoadSound(static_cast<int>(SwordSoundType::ATTACK), "Sound/swingC.wav");
	InitSoundSource(static_cast<int>(SwordSoundType::ATTACK), soundMap_[static_cast<int>(SwordSoundType::ATTACK)]);
}

void SwordSoundComponent::Update()
{
	SoundComponent::Update();

	Reset();
}

void SwordSoundComponent::Render()
{
	SoundComponent::Render();
}

void SwordSoundComponent::Term()
{
	SoundComponent::Term();
}

void SwordSoundComponent::Reset()
{
	SoundComponent::Reset();
}

void SwordSoundComponent::HandleMessage(const IEventMessage& _msg)
{
	const SwordAnimationKeyframeMsg* swordAnimationKeyframeMsg = TypeidSystem::SafeCast<SwordAnimationKeyframeMsg>(&_msg);

	if (swordAnimationKeyframeMsg)
	{
		AddTask([=]()->void
			{
				PlaySoundByID(static_cast<int>(SwordSoundType::ATTACK));
			});
	}

}