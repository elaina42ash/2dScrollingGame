#include "Component/Apple/AppleTileMapSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
#include "Event/IMessenger.h"


AppleTileMapSensorComponent::AppleTileMapSensorComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : TileMapSensorComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

AppleTileMapSensorComponent::AppleTileMapSensorComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : TileMapSensorComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void AppleTileMapSensorComponent::Init()
{
	TileMapSensorComponent::Init();
}

void AppleTileMapSensorComponent::Update()
{
	TileMapSensorComponent::Update();

	Reset();
}

void AppleTileMapSensorComponent::Render()
{
	TileMapSensorComponent::Render();
}

void AppleTileMapSensorComponent::Term()
{
	TileMapSensorComponent::Term();
}

bool AppleTileMapSensorComponent::IsInsideWall(const Vector2f& _position) const
{
	Fwk::Collision::ShapeType shapeType = collisionComponent_->GetShapeType();

	switch (shapeType)
	{
	case Fwk::Collision::ShapeType::Circle:
	{
		if (!droppedObjectView_)
			return true;
		return droppedObjectView_->IsInsideWallCircle(_position, collisionComponent_->GetShapeCircle().radius);
	}

	case Fwk::Collision::ShapeType::Rect:
	{
		if (!droppedObjectView_)
			return true;
		return droppedObjectView_->IsInsideWallRect(_position, collisionComponent_->GetShapeRect().width, collisionComponent_->GetShapeRect().height);
	}
	default:
		return false;
	}
}

void AppleTileMapSensorComponent::Reset()
{
	TileMapSensorComponent::Reset();
}
