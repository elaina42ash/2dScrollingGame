#pragma once
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
#include "Player/IPlayerView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class PlayerTileMapSensorComponent : public TileMapSensorComponent
{
private:
	Inject<IPlayerView> playerView_;

public:
	PlayerTileMapSensorComponent(bool _isActive, IMessenger* _messenger, IPlayerView* _playerView);

	PlayerTileMapSensorComponent(IMessenger* _messenger, IPlayerView* _playerView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	bool IsInsideWall(const Vector2f& _position) const override;

protected:
	void Reset() override;

};
#pragma warning(pop)
