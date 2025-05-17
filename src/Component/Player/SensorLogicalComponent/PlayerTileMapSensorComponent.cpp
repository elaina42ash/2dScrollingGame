#include "Component/Player/SensorLogicalComponent/Class/PlayerTileMapSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
#include "Event/IMessenger.h"

PlayerTileMapSensorComponent::PlayerTileMapSensorComponent(bool _isActive, IMessenger* _messenger): ::TileMapSensorComponent(_isActive, _messenger)
{
}

PlayerTileMapSensorComponent::PlayerTileMapSensorComponent(IMessenger* _messenger): TileMapSensorComponent(_messenger)
{
}

void PlayerTileMapSensorComponent::Init()
{
	TileMapSensorComponent::Init();
}

void PlayerTileMapSensorComponent::Update()
{
	TileMapSensorComponent::Update();

	Reset();
}

void PlayerTileMapSensorComponent::Render()
{
	TileMapSensorComponent::Render();
}

void PlayerTileMapSensorComponent::Term()
{
	TileMapSensorComponent::Term();
}

void PlayerTileMapSensorComponent::Reset()
{
	TileMapSensorComponent::Reset();
}
