#pragma once
#include "Component/Common/SensorLogicalComponent/Class/CollisionComponent.h"
#include "Player/IPlayerView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class PlayerCollisionComponent : public CollisionComponent
{
private:
	Inject<IPlayerView> playerView_;
public:
	PlayerCollisionComponent(bool _isActive, IMessenger* _messenger, IPlayerView* _playerView);

	PlayerCollisionComponent(IMessenger* _messenger, IPlayerView* _playerView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	void Reset() override;

	void OnCollision(const Fwk::Collision::Collider& _me, const Fwk::Collision::Collider& _other) override;

public:
	void HandleMessage(const IEventMessage& _msg) override;
};
#pragma warning(pop)