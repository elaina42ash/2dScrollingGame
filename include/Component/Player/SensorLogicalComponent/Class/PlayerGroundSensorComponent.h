#pragma once
#include "Component/Common/SensorLogicalComponent/Class/GroundSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ITileMapSensorComponent.h"
#include "Player/IPlayerView.h"
#pragma warning(push)
#pragma warning(disable:4250)
class PlayerGroundSensorComponent : public GroundSensorComponent
{
private:
	Inject<ITileMapSensorComponent> tileMapSensorComponent_;

	Inject<IPlayerView> playerView_;

	Lib::Math::Vector2f rayVec_ = {0.0f,-21.0f};

public:
	PlayerGroundSensorComponent(bool _isActive, IMessenger* _messenger, IPlayerView* _playerView);

	PlayerGroundSensorComponent(IMessenger* _messenger, IPlayerView* _playerView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	void Reset() override;
};
#pragma warning(pop)