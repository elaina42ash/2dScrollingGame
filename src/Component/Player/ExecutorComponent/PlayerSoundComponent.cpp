#include "Component/Player/ExecutorComponent/Class/PlayerSoundComponent.h"
#include "Component/Common/ExecutorComponent/Class/SoundComponent.h"
#include "Event/Message/SemanticMsg/StartJumpSemMsg.h"
#include "Event/Message/SemanticMsg/StartKnockBackSemMsg.h"
#include "Sound/SoundDef.h"

PlayerSoundComponent::PlayerSoundComponent(bool _isActive, IMessenger* _messenger) : SoundComponent(_isActive, _messenger)
{
}

void PlayerSoundComponent::Init()
{
	SoundComponent::Init();

	// Waveデータ読み込み
	LoadSound(static_cast<int>(PlayerSoundType::JUMP), "Sound/jumpC.wav");
	LoadSound(static_cast<int>(PlayerSoundType::KNOCK_BACK), "Sound/damageB.wav");

	// 音源
	InitSoundSource(static_cast<int>(PlayerSoundType::JUMP), soundMap_[static_cast<int>(PlayerSoundType::JUMP)]);
	InitSoundSource(static_cast<int>(PlayerSoundType::KNOCK_BACK), soundMap_[static_cast<int>(PlayerSoundType::KNOCK_BACK)]);
}

void PlayerSoundComponent::Update()
{
	SoundComponent::Update();

	Reset();
}

void PlayerSoundComponent::Render()
{
	SoundComponent::Render();
}

void PlayerSoundComponent::Term()
{
	SoundComponent::Term();
}

void PlayerSoundComponent::HandleMessage(const IEventMessage& _msg)
{
	const StartJumpSemMsg* startJumpSemMsg = TypeidSystem::SafeCast<StartJumpSemMsg>(&_msg);
	const StartKnockBackSemMsg* startKnockBackSemMsg = TypeidSystem::SafeCast<StartKnockBackSemMsg>(&_msg);

	if (startJumpSemMsg)
	{
		AddTask([=]()->void
			{
				PlaySoundByID(static_cast<int>(PlayerSoundType::JUMP));
			});
	}

	if (startKnockBackSemMsg)
	{
		AddTask([=]()->void
			{
				PlaySoundByID(static_cast<int>(PlayerSoundType::KNOCK_BACK));
			});
	}
}

void PlayerSoundComponent::Reset()
{
	SoundComponent::Reset();
}
