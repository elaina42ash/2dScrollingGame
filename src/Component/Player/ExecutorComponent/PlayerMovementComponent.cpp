#include "Component/Player/ExecutorComponent/Class/PlayerMovementComponent.h"
#include <iostream>
#include "GameMath.h"
#include "Component/Common/ExecutorComponent/Class/MovementComponent.h"
#include "Fwk/Framework.h"

PlayerMovementComponent::PlayerMovementComponent(bool _isActive, IPlayerView* _playerView, IMessenger* _messenger) : MovementComponent(_isActive, _messenger),
playerView_(_playerView)
{
}

PlayerMovementComponent::PlayerMovementComponent(IPlayerView* _playerView, IMessenger* _messenger) :MovementComponent(_messenger), playerView_(_playerView)
{
}


void PlayerMovementComponent::Move(const Lib::Math::Vector2f& _velocity)
{
#ifdef max
#undef max
#endif
	constexpr float epsilon = 1e-2f;

	if (!collisionComponent_)
	{
		cout << "collisionComponent_ is nullptr" << endl;
		return;
	}
	if (!tileMapSensorComponent_)
	{
		cout << "tileMapSensorComponent_ is nullptr" << endl;
		return;
	}

	// タイルのサイズ
	Tilemap* tilemap = GetMap();
	if (!tilemap)
	{
		cout << "tilemap not fund" << endl;
		return;
	}
	float TileSize = tilemap->GetTileSize();

	// プレイヤーのタイルとの衝突幅・高さ
	float CollisionSize;
	switch (collisionComponent_->GetShapeType())
	{
	case ShapeType::Circle:
		CollisionSize = collisionComponent_->GetShapeCircle().radius;
		break;
	case ShapeType::Rect:
		CollisionSize = max(collisionComponent_->GetShapeRect().width, collisionComponent_->GetShapeRect().height);
		break;
	default:
		CollisionSize = 0.0f;
		cout << "ShapeType is None" << endl;
		return;
	}

	// コリジョンサイズの半分をよく使うので変数にしておく
	float CollisionSizeHalf = CollisionSize / 2.0f;

	// x軸方向の移動処理
	if (!GameMath::FloatIsZero(_velocity.x))
	{
		// 現在位置に移動ベクトルのx成分を足して移動先の位置とする
		Vector2f vTargetPos = transformComponent_->GetPosition() + Lib::Math::Vector2f(_velocity.x, 0.0f);
		// 壁との衝突チェック
		if (!tileMapSensorComponent_->IsInsideWall(vTargetPos))
		{
			// 壁に衝突しないのであれば現在位置にそのまま移動先座標を適用してよい
			transformComponent_->MoveTo(vTargetPos);
		}
		else
		{
			// 壁に衝突する場合の処理
			// 右向きに移動しようとしていた場合
			if (_velocity.x > 0.0f)
			{
				// 衝突したタイルの列数を算出
				int col = (int)((vTargetPos.x + CollisionSizeHalf) / TileSize);
				// 衝突したタイルの左端のx座標を作る
				float tile_left = (float)col * TileSize;
				// 衝突したタイルの左端と接するようにプレイヤーの位置を調整する
				transformComponent_->MoveTo({ tile_left - CollisionSizeHalf - epsilon,transformComponent_->GetPositionY() });
			}
			// 左向きに移動しようとしていた場合
			if (_velocity.x < 0.0f)
			{
				// 衝突したタイルの列数を算出
				int col = (int)((vTargetPos.x - CollisionSizeHalf) / TileSize);
				// 衝突したタイルの右端のx座標を作って
				float tile_right = (float)col * TileSize + TileSize;
				// 衝突したタイルの右端に接するようにプレイヤーの位置を調整する
				transformComponent_->MoveTo({ tile_right + CollisionSizeHalf + epsilon,transformComponent_->GetPositionY() });
			}
		}
	}

	// Y軸方向の移動処理
	if (!GameMath::FloatIsZero(_velocity.y))
	{
		// 現在位置に移動ベクトルのy成分を足して移動先の位置とする
		Vector2f vTargetPos = transformComponent_->GetPosition() + Vector2f(0.0f, _velocity.y);
		// 壁との衝突チェック
		if (!tileMapSensorComponent_->IsInsideWall(vTargetPos))
		{
			// 壁に衝突しないのであれば現在位置にそのまま移動先座標を適用
			transformComponent_->MoveTo(vTargetPos);
		}
		else
		{
			// 上向きに移動しようとしていた場合
			if (_velocity.y > 0.0f)
			{
				// 衝突したタイルの行数を算出
				int row = static_cast<int>((vTargetPos.y + CollisionSizeHalf) / TileSize);
				// 衝突したタイルの下端のy座標を作って
				float wall_buttom = static_cast<float>(row) * TileSize - TileSize;
				// 衝突したタイルの下端に接するようにプレイヤーの位置を調整する
				transformComponent_->MoveTo({ transformComponent_->GetPositionX(), wall_buttom - CollisionSizeHalf - epsilon });
				if (physicsComponent_)
					physicsComponent_->ClearVerticalVelocity();
			}
			// 下向きに移動しようとしていた場合
			if (_velocity.y < 0.0f)
			{
				// 衝突したタイルの行数を算出
				int row = static_cast<int>((vTargetPos.y - CollisionSizeHalf) / TileSize);
				// 衝突したタイルの上端のy座標を作って
				float wall_top = static_cast<float>(row) * TileSize;
				// 衝突したタイルの上端に接するようにプレイヤーの位置を調整する
				transformComponent_->MoveTo({ transformComponent_->GetPositionX(), wall_top + CollisionSizeHalf + epsilon });
				if (physicsComponent_)
					physicsComponent_->ClearVerticalVelocity();
			}
		}
	}
}

void PlayerMovementComponent::Init()
{
	MovementComponent::Init();
}

void PlayerMovementComponent::Update()
{
	MovementComponent::Update();

	Move(playerView_->GetVelocity());

	Reset();
}

void PlayerMovementComponent::Render()
{
	MovementComponent::Render();
}

void PlayerMovementComponent::Term()
{
	MovementComponent::Term();
}

void PlayerMovementComponent::HandleMessage(const IEventMessage& _msg)
{

}

void PlayerMovementComponent::Reset()
{
	MovementComponent::Reset();
}
