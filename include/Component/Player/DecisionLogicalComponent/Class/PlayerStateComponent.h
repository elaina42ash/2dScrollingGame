#pragma once
#include "IInputCacheProvider .h"
#include "Component/Common/DecisionLogicalComponent/Class/StateComponent.h"
#include "Player/IPlayerView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class PlayerStateComponent : public StateComponent, public IInputCacheProvider
{
private:
	Inject<IPlayerView> playerView_;

	Lib::Math::Vector2f inputCacheForState = { 0.0f,0.0f };

	bool isStageCleared_ = false;

	bool isGameVictory_ = false;

	float dashCooldown_ = 0.0f;
public:
	PlayerStateComponent(bool _isActive, IMessenger* _messenger, IPlayerView* _playerView);

	PlayerStateComponent(IMessenger* _messenger, IPlayerView* _playerView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

	Lib::Math::Vector2f GetInputCache() const override;

	bool IsStageCleared() const;

	bool IsGameVictory() const;

	bool IsDashCooldown() const;

	void SetDashCooldown(float _cooldown);

protected:
	void Reset() override;

private:
	void SetInputCache(const Lib::Math::Vector2f& _inputCache);

	void InitializeMotionStateMachine(InnerStateMachine* motionStateMachine);

};

inline void PlayerStateComponent::SetDashCooldown(float _cooldown)
{
	dashCooldown_ = _cooldown;
}

inline bool PlayerStateComponent::IsDashCooldown() const
{
	if (dashCooldown_ > 0.0f)
		return true;
	else
		return false;
}
#pragma warning(pop)
