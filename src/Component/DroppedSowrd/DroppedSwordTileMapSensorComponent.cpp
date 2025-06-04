#include "Component/DroppedSword/DroppedSwordTileMapSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
#include "Event/IMessenger.h"


DroppedSwordTileMapSensorComponent::DroppedSwordTileMapSensorComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView): TileMapSensorComponent(_isActive, _messenger),
	                                         droppedObjectView_(_droppedObjectView)
{
}

DroppedSwordTileMapSensorComponent::DroppedSwordTileMapSensorComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView): TileMapSensorComponent(_messenger),
	                                         droppedObjectView_(_droppedObjectView)
{
}

void DroppedSwordTileMapSensorComponent::Init()
{
	TileMapSensorComponent::Init();
}

void DroppedSwordTileMapSensorComponent::Update()
{
	TileMapSensorComponent::Update();

	Reset();
}

void DroppedSwordTileMapSensorComponent::Render()
{
	TileMapSensorComponent::Render();
}

void DroppedSwordTileMapSensorComponent::Term()
{
	TileMapSensorComponent::Term();
}

bool DroppedSwordTileMapSensorComponent::IsInsideWall(const Vector2f& _position) const
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

void DroppedSwordTileMapSensorComponent::Reset()
{
	TileMapSensorComponent::Reset();
}
