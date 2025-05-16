#include "Component/Common/ExecutorComponent/Class/SoundComponent.h"

SoundComponent::SoundComponent(bool _isActive, IMessenger* _messenger) : ExecutorComponent(_isActive, _messenger)
{
}

void SoundComponent::LoadSound(SoundID _id, const char* _filename)
{
	soundMap_[_id].Load(_filename);
}

void SoundComponent::InitSoundSource(SoundID _id, const IWaveData& _waveData)
{
	soundSourceMap_[_id].Init(_waveData);
}

void SoundComponent::PlaySoundByID(SoundID _id)
{
	auto it = soundSourceMap_.find(_id);
	if (it == soundSourceMap_.end())
		return;
	it->second.Play();
}

void SoundComponent::Init()
{
	ExecutorComponent::Init();
}

void SoundComponent::Update()
{
	ExecutorComponent::Update();
}

void SoundComponent::Render()
{
	ExecutorComponent::Render();
}

void SoundComponent::Term()
{
	ExecutorComponent::Term();

	// サウンドの解放
	for (auto it = soundMap_.begin(); it != soundMap_.end(); ++it)
	{
		it->second.Unload();
	}
	for (auto it = soundSourceMap_.begin(); it != soundSourceMap_.end(); ++it)
	{
		it->second.Term();
	}

}

void SoundComponent::Reset()
{
	ExecutorComponent::Reset();
}
