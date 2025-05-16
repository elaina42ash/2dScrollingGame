#include "Component/Player/SensorLogicalComponent/Class/PlayerTileMapSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
#include "Event/IMessenger.h"
#include "GameObjectMng/GameObjectMng.h"

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

bool PlayerTileMapSensorComponent::IsInsideWall(Lib::Math::Vector2f _position) const
{
	ShapeType shapeType = collisionComponent_->GetShapeType();
	switch (shapeType)
	{
	case ShapeType::Circle:
		return GetMap()->IsInsideWallCircle(_position, collisionComponent_->GetShapeCircle().radius);
	case ShapeType::Rect:
		return GetMap()->IsInsideWallRect(_position, collisionComponent_->GetShapeRect().width, collisionComponent_->GetShapeRect().height);
	default:
		return false;
	}
}