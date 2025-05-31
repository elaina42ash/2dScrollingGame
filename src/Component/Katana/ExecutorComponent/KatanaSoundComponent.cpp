#include "Component/Katana/ExecutorComponent/KatanaSoundComponent.h"
#include "Event/Message/AnimationMsg/KatanaAnimationKeyframeMsg.h"
#include "Sound/SoundDef.h"

KatanaSoundComponent::KatanaSoundComponent(bool _isActive, IWeaponView* _weaponView, IMessenger* _messenger) : SoundComponent(_isActive, _messenger), weaponView_(_weaponView)
{

}

void KatanaSoundComponent::Init()
{
	SoundComponent::Init();

	LoadSound(static_cast<int>(KatanaSoundType::ATTACK), "Sound/swingC.wav");
	InitSoundSource(static_cast<int>(KatanaSoundType::ATTACK), soundMap_[static_cast<int>(KatanaSoundType::ATTACK)]);
}

void KatanaSoundComponent::Update()
{
	SoundComponent::Update();

	Reset();
}

void KatanaSoundComponent::Render()
{
	SoundComponent::Render();
}

void KatanaSoundComponent::Term()
{
	SoundComponent::Term();
}

void KatanaSoundComponent::Reset()
{
	SoundComponent::Reset();
}

void KatanaSoundComponent::HandleMessage(const IEventMessage& _msg)
{
	const KatanaAnimationKeyframeMsg* katanaAnimationKeyframe = TypeidSystem::SafeCast<KatanaAnimationKeyframeMsg>(&_msg);

	if (katanaAnimationKeyframe)
	{
		AddTask([=]()->void
			{
				PlaySoundByID(static_cast<int>(KatanaSoundType::ATTACK));
			});
	}

}