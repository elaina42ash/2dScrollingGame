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

float TileMapSensorComponent::GetTileSize() const
{
	if (!environmentQuery_)
		return 0.0f;

	return environmentQuery_->GetTileSize();
}

Vector2f TileMapSensorComponent::GetMapSize() const
{
	if (!environmentQuery_)
		return {0.0f,0.0f};

	return environmentQuery_->GetMapSize();
}

bool TileMapSensorComponent::IsInsideWall(const Vector2f& _position) const
{
	Fwk::Collision::ShapeType shapeType = collisionComponent_->GetShapeType();

	if (!environmentQuery_)
		return true;

	switch (shapeType)
	{
	case Fwk::Collision::ShapeType::Circle:
		return environmentQuery_->IsInsideWallCircle(_position, collisionComponent_->GetShapeCircle().radius);
	case Fwk::Collision::ShapeType::Rect:
		return environmentQuery_->IsInsideWallRect(_position, collisionComponent_->GetShapeRect().width, collisionComponent_->GetShapeRect().height);
	default:
		return false;
	}
}

void TileMapSensorComponent::InjectEnvironmentQuery(IEnvironmentQuery* _environmentQuery)
{
	environmentQuery_.Bind(_environmentQuery);
}


void TileMapSensorComponent::Reset()
{
	SensorLogicalComponent::Reset();
}


