#pragma once
#include "Component/Common/ExecutorComponent/Class/AnimationComponent.h"
#include "Event/IMessenger.h"
#include "Player/IPlayerView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class PlayerAnimationComponent : public AnimationComponent
{
	using AnimationID = int;
private:
	Inject<IPlayerView> playerView_;

public:
	PlayerAnimationComponent(bool _isActive, IMessenger* messenger_, IPlayerView* _playerView);

	PlayerAnimationComponent(IMessenger* messenger_, IPlayerView* _playerView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;

	void RegisterPlayerAnimation();
	void AddPlayerIdleAnimationTask();

private:
};
#pragma warning(pop)