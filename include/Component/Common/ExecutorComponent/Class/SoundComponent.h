#pragma once
#include "ExecutorComponent.h"
#include "Component/Common/ExecutorComponent/Interface/ISoundComponent.h"
#include "Fwk/Audio/SoundSource.h"
#include "Fwk/Audio/WaveSound.h"

#pragma warning(push)
#pragma warning(disable:4250)
class SoundComponent : public ExecutorComponent, public ISoundComponent
{
	using SoundID = int;
protected:

	// 効果音
	std::unordered_map<SoundID,WaveSound> soundMap_;

	// 音源
	std::unordered_map<SoundID, SoundSource> soundSourceMap_;

protected:
	explicit SoundComponent(bool _isActive,IMessenger* _messenger);

	void LoadSound(SoundID _id, const char* _filename);

	void InitSoundSource(SoundID _id, const IWaveData& _waveData);

	void PlaySoundByID(SoundID _id);

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	void Reset() override;
};
#pragma warning(pop)