#include "Component/DroppedKatana/DroppedKatanaTileMapSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
#include "Event/IMessenger.h"


DroppedKatanaTileMapSensorComponent::DroppedKatanaTileMapSensorComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : TileMapSensorComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedKatanaTileMapSensorComponent::DroppedKatanaTileMapSensorComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : TileMapSensorComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void DroppedKatanaTileMapSensorComponent::Init()
{
	TileMapSensorComponent::Init();
}

void DroppedKatanaTileMapSensorComponent::Update()
{
	TileMapSensorComponent::Update();

	Reset();
}

void DroppedKatanaTileMapSensorComponent::Render()
{
	TileMapSensorComponent::Render();
}

void DroppedKatanaTileMapSensorComponent::Term()
{
	TileMapSensorComponent::Term();
}

bool DroppedKatanaTileMapSensorComponent::IsInsideWall(const Vector2f& _position) const
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

void DroppedKatanaTileMapSensorComponent::Reset()
{
	TileMapSensorComponent::Reset();
}
