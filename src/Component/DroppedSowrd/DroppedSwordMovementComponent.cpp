#include "Component/DroppedSword/DroppedSwordMovementComponent.h"
#include <iostream>
#include <ostream>
#include "GameMath.h"
#include "Component/Common/ExecutorComponent/Class/AnimationComponent.h"


DroppedSwordMovementComponent::DroppedSwordMovementComponent(bool _isActive, IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : MovementComponent(_isActive, _messenger),
	droppedObjectView_(_droppedObjectView)
{
}

DroppedSwordMovementComponent::DroppedSwordMovementComponent(IMessenger* _messenger,
	IDroppedObjectView* _droppedObjectView) : MovementComponent(_messenger),
	droppedObjectView_(_droppedObjectView)
{
}

void DroppedSwordMovementComponent::Move(const Lib::Math::Vector2f& _velocity)
{
#ifdef max
#undef max
#endif
	constexpr float epsilon = 1e-2f;

	// タイルのサイズ
	float TileSize = 0.0f;
	if (droppedObjectView_)
		TileSize = droppedObjectView_->GetTileSize();

	// コリジョンサイズ（幅・高さ）
	float CollisionWidth = 0.0f;
	float CollisionHeight = 0.0f;
	Fwk::Collision::ShapeType shapeType = Fwk::Collision::ShapeType::None;

	if (collisionComponent_)
	{
		shapeType = collisionComponent_->GetShapeType();
		switch (shapeType)
		{
		case Fwk::Collision::ShapeType::Circle:
		{
			float diameter = collisionComponent_->GetShapeCircle().radius * 2.0f;
			CollisionWidth = diameter;
			CollisionHeight = diameter;
			break;
		}
		case Fwk::Collision::ShapeType::Rect:
		{
			auto rect = collisionComponent_->GetShapeRect();
			CollisionWidth = rect.width;
			CollisionHeight = rect.height;
			break;
		}
		default:
			std::cout << "ShapeType is None" << std::endl;
			return;
		}
	}

	// --------------------------------------------
	// 左上座標 → 中心座標へ一時的に変換して処理
	// --------------------------------------------
	Vector2f leftTop = transformComponent_->GetPosition(); // 現在のtransformは左上座標
	Vector2f center = leftTop + Vector2f(CollisionWidth, CollisionHeight) * 0.5f;
	Vector2f targetCenter = center;

	// X軸方向の移動処理（中心ベース）
	if (!GameMath::FloatIsZero(_velocity.x))
	{
		targetCenter.x += _velocity.x;

		bool isInsideWall = true;
		if (tileMapSensorComponent_)
			isInsideWall = tileMapSensorComponent_->IsInsideWall(targetCenter);

		if (isInsideWall)
		{
			if (_velocity.x > 0.0f)
			{
				int col = static_cast<int>((targetCenter.x + CollisionWidth * 0.5f) / TileSize);
				float tile_left = static_cast<float>(col) * TileSize;
				targetCenter.x = tile_left - CollisionWidth * 0.5f - epsilon;
			}
			else if (_velocity.x < 0.0f)
			{
				int col = static_cast<int>((targetCenter.x - CollisionWidth * 0.5f) / TileSize);
				float tile_right = static_cast<float>(col) * TileSize + TileSize;
				targetCenter.x = tile_right + CollisionWidth * 0.5f + epsilon;
			}
		}
	}

	// Y軸方向の移動処理（中心ベース）
	if (!GameMath::FloatIsZero(_velocity.y))
	{
		targetCenter.y += _velocity.y;

		bool isInsideWall = true;
		if (tileMapSensorComponent_)
			isInsideWall = tileMapSensorComponent_->IsInsideWall(targetCenter);

		if (isInsideWall)
		{
			if (_velocity.y > 0.0f)
			{
				int row = static_cast<int>((targetCenter.y + CollisionHeight * 0.5f) / TileSize);
				float wall_bottom = static_cast<float>(row) * TileSize - TileSize;
				targetCenter.y = wall_bottom - CollisionHeight * 0.5f - epsilon;
				if (physicsComponent_)
					physicsComponent_->ClearVerticalVelocity();
			}
			else if (_velocity.y < 0.0f)
			{
				int row = static_cast<int>((targetCenter.y - CollisionHeight * 0.5f) / TileSize);
				float wall_top = static_cast<float>(row) * TileSize;
				targetCenter.y = wall_top + CollisionHeight * 0.5f + epsilon;
				if (physicsComponent_)
					physicsComponent_->ClearVerticalVelocity();
			}
		}
	}

	// --------------------------------------------
	// 中心座標 → 左上座標に戻してtransformへ反映
	// --------------------------------------------
	Vector2f newLeftTop = targetCenter - Vector2f(CollisionWidth, CollisionHeight) * 0.5f;
	transformComponent_->MoveTo(newLeftTop);
}





void DroppedSwordMovementComponent::Init()
{
	MovementComponent::Init();
}

void DroppedSwordMovementComponent::Update()
{
	MovementComponent::Update();

	Move(droppedObjectView_->GetVelocity());

	Reset();
}

void DroppedSwordMovementComponent::Render()
{
	MovementComponent::Render();
}

void DroppedSwordMovementComponent::Term()
{
	MovementComponent::Term();
}

void DroppedSwordMovementComponent::HandleMessage(const IEventMessage& _msg)
{

}

void DroppedSwordMovementComponent::Reset()
{
	MovementComponent::Reset();
}
