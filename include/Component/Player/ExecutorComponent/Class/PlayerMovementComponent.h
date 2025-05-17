#pragma once
#include "Component/Common/ExecutorComponent/Class/MovementComponent.h"
#include "GameObjectMng/GameObjectMng.h"
#include "Player/IPlayerView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class PlayerMovementComponent : public MovementComponent
{
private:
	Inject<IPlayerView> playerView_;

public:
	PlayerMovementComponent(bool _isActive, IPlayerView* _playerView,IMessenger* _messenger);

	explicit PlayerMovementComponent(IPlayerView* _playerView, IMessenger* _messenger);

private:
	void Move(const Lib::Math::Vector2f& _velocity) override;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

protected:
	void Reset() override;
};
#pragma warning(pop)
