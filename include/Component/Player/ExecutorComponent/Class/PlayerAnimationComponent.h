#pragma once
#include "Component/Common/ExecutorComponent/Class/AnimationComponent.h"
#include "Event/IMessenger.h"
#include "Event/Message/AnimationMsg/SwordAnimationBeginMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationCompletedMsg.h"
#include "Event/Message/AnimationMsg/SwordAnimationKeyframeMsg.h"
#include "Player/IPlayerView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class PlayerAnimationComponent : public AnimationComponent
{
	using AnimationID = int;
private:
	const char* IDLE_ANIMATION_URL = "Images/2dAction/Player/Player.png";

	const int MAX_ANIMATION_FRAMES = 12;
	const int MAX_ANIMATION_TYPE = 4;
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

	void OnAnimationEvent(const AnimationEvent& _animEvent) override;

	void Reset() override;

	void InitAnimationFrames(float _uvWidth, float _uvHeight, int _frameCount, int _animationResourceRowIndex,
	                         vector<UVRect>& _idleAnimationFrames);

	void RegisterPlayerAnimation();

private:
	void OnKatanaAnimationEvent(const AnimationEvent& _animEvent);

	void OnSwordAnimationEvent(const AnimationEvent& _animEvent);
};
#pragma warning(pop)