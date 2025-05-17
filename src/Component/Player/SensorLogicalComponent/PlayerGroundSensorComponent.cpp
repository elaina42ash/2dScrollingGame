#include "Component/Player/SensorLogicalComponent/Class/PlayerGroundSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Class/GroundSensorComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ITileMapSensorComponent.h"
#include "Event/IMessenger.h"
#include "Lib/Math/TVector2.h"

PlayerGroundSensorComponent::PlayerGroundSensorComponent(bool _isActive, IMessenger* _messenger,
	IPlayerView* _playerView) : ::GroundSensorComponent(_isActive, _messenger),
	playerView_(_playerView)
{
}

PlayerGroundSensorComponent::PlayerGroundSensorComponent(IMessenger* _messenger, IPlayerView* _playerView) : GroundSensorComponent(_messenger),
playerView_(_playerView)
{
}

void PlayerGroundSensorComponent::Init()
{
	GroundSensorComponent::Init();
	tileMapSensorComponent_.Bind(GetComponent<ITileMapSensorComponent>());

	ICollisionComponent* collisionComponent = GetComponent<ICollisionComponent>();

	if (collisionComponent)
	{
		float value = 0.0f;

		switch (collisionComponent->GetShapeType())
		{
		case Fwk::Collision::ShapeType::Rect:
			value = -(collisionComponent->GetShapeRect().height / 2.0f + 1.0f);
			break;
		case Fwk::Collision::ShapeType::Circle:
			value = -(collisionComponent->GetShapeCircle().radius / 2.0f + 1.0f);
			break;
		default:
			break;
		}

		rayVec_.y += value;

		lineSensor_->SetRayVec(rayVec_);
	}

}

void PlayerGroundSensorComponent::Update()
{
	GroundSensorComponent::Update();

	if (lineSensor_)
		lineSensor_->SetPosition(playerView_->GetPosition());

	Vector2f endPoint = {0.0f,0.0f};

	if (lineSensor_)
		endPoint = lineSensor_->GetEndPoint();

	
	if (tileMapSensorComponent_)
		SetDetectedResult(tileMapSensorComponent_->IsInsideWall(endPoint));

}

void PlayerGroundSensorComponent::Render()
{
	GroundSensorComponent::Render();
}

void PlayerGroundSensorComponent::Term()
{
	GroundSensorComponent::Term();
}

void PlayerGroundSensorComponent::Reset()
{
	GroundSensorComponent::Reset();
}
