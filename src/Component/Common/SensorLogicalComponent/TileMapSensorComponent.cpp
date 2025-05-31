#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
TileMapSensorComponent::TileMapSensorComponent(bool _isActive, IMessenger* _messenger): SensorLogicalComponent(_isActive, _messenger)
{

}

TileMapSensorComponent::TileMapSensorComponent(IMessenger* _messenger): SensorLogicalComponent(_messenger)
{

}

void TileMapSensorComponent::Init()
{
	SensorLogicalComponent::Init();
	collisionComponent_.Bind(GetComponent<ICollisionComponent>());
}

void TileMapSensorComponent::Update()
{
	SensorLogicalComponent::Update();
}

void TileMapSensorComponent::Render()
{
	SensorLogicalComponent::Render();
}

void TileMapSensorComponent::Term()
{
	SensorLogicalComponent::Term();
}


void TileMapSensorComponent::Reset()
{
	SensorLogicalComponent::Reset();
}


