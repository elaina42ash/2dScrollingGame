#include "Component/Player/SensorLogicalComponent/Class/PlayerTileMapSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
#include "Event/IMessenger.h"

PlayerTileMapSensorComponent::PlayerTileMapSensorComponent(bool _isActive, IMessenger* _messenger, IPlayerView* _playerView): TileMapSensorComponent(_isActive, _messenger),playerView_(_playerView)
{
}

PlayerTileMapSensorComponent::PlayerTileMapSensorComponent(IMessenger* _messenger, IPlayerView* _playerView): TileMapSensorComponent(_messenger), playerView_(_playerView)
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

bool PlayerTileMapSensorComponent::IsInsideWall(const Vector2f& _position) const
{
	Fwk::Collision::ShapeType shapeType = collisionComponent_->GetShapeType();

	switch (shapeType)
	{
	case Fwk::Collision::ShapeType::Circle:
		{
			if (!playerView_)
				return true;
			return playerView_->IsInsideWallCircle(_position, collisionComponent_->GetShapeCircle().radius);
		}

	case Fwk::Collision::ShapeType::Rect:
		{
			if (!playerView_)
				return true;
			return playerView_->IsInsideWallRect(_position, collisionComponent_->GetShapeRect().width, collisionComponent_->GetShapeRect().height);
		}
	default:
		return false;
	}
}

void PlayerTileMapSensorComponent::Reset()
{
	TileMapSensorComponent::Reset();
}
