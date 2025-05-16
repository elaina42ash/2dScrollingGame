#pragma once
#include "Component.h"
#include "Fwk/Audio/SoundSource.h"

class PlayerSoundComponent : public Component
{
public:
private:
	// 使う効果音の種類
	enum class Sound {
		Jump,
		Damaged,
		Count
	};
private:
	// 効果音
	/*WaveSound mSounds[(int)Sound::Count];*/
	// 音源
	SoundSource mSoundSources[(int)Sound::Count];
};
