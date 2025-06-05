#include "Component/Apple/AppleMovementComponent.h"
#include <iostream>
#include <ostream>
#include "GameMath.h"
#include "Component/Common/ExecutorComponent/Class/AnimationComponent.h"


AppleMovementComponent::AppleMovementComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : MovementComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

AppleMovementComponent::AppleMovementComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : MovementComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void AppleMovementComponent::Move(const Lib::Math::Vector2f& _velocity)
{
#ifdef max
#undef max
#endif
	constexpr float epsilon = 1e-2f;

	// タイルのサイズ
	float TileSize = 0.0f;

	if (droppedObjectView_)
		TileSize = droppedObjectView_->GetTileSize();

	Fwk::Collision::ShapeType shapeType = Fwk::Collision::ShapeType::None;

	// プレイヤーのタイルとの衝突幅・高さ
	float CollisionSize = 0.0f;
	if (collisionComponent_)
	{
		shapeType = collisionComponent_->GetShapeType();
		switch (shapeType)
		{
		case Fwk::Collision::ShapeType::Circle:
			CollisionSize = collisionComponent_->GetShapeCircle().radius;
			break;
		case Fwk::Collision::ShapeType::Rect:
			CollisionSize = std::max(collisionComponent_->GetShapeRect().width, collisionComponent_->GetShapeRect().height);
			break;
		default:
			std::cout << "ShapeType is None" << std::endl;
			return;
		}
	}

	// コリジョンサイズの半分をよく使うので変数にしておく
	float CollisionSizeHalf = CollisionSize / 2.0f;

	Vector2f targetPos = { 0.0f ,0.0f };

	// X軸方向の移動処理
	if (transformComponent_ && !GameMath::FloatIsZero(_velocity.x))
	{
		targetPos = transformComponent_->GetPosition() + Lib::Math::Vector2f(_velocity.x, 0.0f);

		bool isInsideWall = true;
		if (tileMapSensorComponent_)
			isInsideWall = tileMapSensorComponent_->IsInsideWall(targetPos);

		if (!isInsideWall)
		{
			transformComponent_->MoveTo(targetPos);
		}
		else
		{
			if (_velocity.x > 0.0f)
			{
				int col = static_cast<int>((targetPos.x + CollisionSizeHalf) / TileSize);
				float tile_left = static_cast<float>(col) * TileSize;
				transformComponent_->MoveTo({ tile_left - CollisionSizeHalf - epsilon, transformComponent_->GetPositionY() });
			}
			else if (_velocity.x < 0.0f)
			{
				int col = static_cast<int>((targetPos.x - CollisionSizeHalf) / TileSize);
				float tile_right = static_cast<float>(col) * TileSize + TileSize;
				transformComponent_->MoveTo({ tile_right + CollisionSizeHalf + epsilon, transformComponent_->GetPositionY() });
			}
		}
	}

	// Y軸方向の移動処理
	if (transformComponent_ && !GameMath::FloatIsZero(_velocity.y))
	{
		targetPos = transformComponent_->GetPosition() + Vector2f(0.0f, _velocity.y);

		bool isInsideWall = true;
		if (tileMapSensorComponent_)
			isInsideWall = tileMapSensorComponent_->IsInsideWall(targetPos);

		if (!isInsideWall)
		{
			transformComponent_->MoveTo(targetPos);
		}
		else
		{
			if (_velocity.y > 0.0f)
			{
				int row = static_cast<int>((targetPos.y + CollisionSizeHalf) / TileSize);
				float wall_bottom = static_cast<float>(row) * TileSize - TileSize;
				transformComponent_->MoveTo({ transformComponent_->GetPositionX(), wall_bottom - CollisionSizeHalf - epsilon });
				if (physicsComponent_)
					physicsComponent_->ClearVerticalVelocity();
			}
			else if (_velocity.y < 0.0f)
			{
				int row = static_cast<int>((targetPos.y - CollisionSizeHalf) / TileSize);
				float wall_top = static_cast<float>(row) * TileSize;
				transformComponent_->MoveTo({ transformComponent_->GetPositionX(), wall_top + CollisionSizeHalf + epsilon });
				if (physicsComponent_)
					physicsComponent_->ClearVerticalVelocity();
			}
		}
	}
}


void AppleMovementComponent::Init()
{
	MovementComponent::Init();
}

void AppleMovementComponent::Update()
{
	MovementComponent::Update();

	Move(droppedObjectView_->GetVelocity());

	Reset();
}

void AppleMovementComponent::Render()
{
	MovementComponent::Render();
}

void AppleMovementComponent::Term()
{
	MovementComponent::Term();
}

void AppleMovementComponent::HandleMessage(const IEventMessage& _msg)
{

}

void AppleMovementComponent::Reset()
{
	MovementComponent::Reset();
}
