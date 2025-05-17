#pragma once
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"

#pragma warning(push)
#pragma warning(disable:4250)
class PlayerTileMapSensorComponent : public TileMapSensorComponent
{
public:
	PlayerTileMapSensorComponent(bool _isActive, IMessenger* _messenger);

	explicit PlayerTileMapSensorComponent(IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	void Reset() override;

};
#pragma warning(pop)
