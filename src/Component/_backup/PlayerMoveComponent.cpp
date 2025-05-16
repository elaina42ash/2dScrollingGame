#include "Player.h"
#include "Component/PlayerMoveComponent.h"

#include "Component/PlayerAnimationComponent.h"
#include "Event/Message/AnimationMessage.h"
#include "Event/Message/BehaviourMessage.h"
#include "Fwk/Framework.h"
#include "GameObjectMng/GameObjectMng.h"

void PlayerMoveComponent::SetFlag(PlayerStateComponent::BehaviourType _behaviour, bool _flag)
{
	auto it = behaviourFlagTable_.find(_behaviour);
	if (it == behaviourFlagTable_.end())
	{
		behaviourFlagTable_.insert({ _behaviour,_flag });
		return;
	}

	it->second = _flag;
}

bool PlayerMoveComponent::GetFlag(PlayerStateComponent::BehaviourType _behaviour)
{
	auto it = behaviourFlagTable_.find(_behaviour);
	if (it == behaviourFlagTable_.end())
		return false;
	return it->second;
}

void PlayerMoveComponent::UpdateVelocity(Lib::Math::Vector2f vInput)
{
	// このフレームでの移動量
	float acceleration = 50.0f * Time_I->GetDeltaTime();
	// このフレームでの最大移動量
	float maxSpeed = 300.0f * Time_I->GetDeltaTime();

	// X軸方向の入力があれば加速する
	if (vInput.x != 0.0f)
	{
		// 速度ベクトルに、加速分のベクトルを足しこむ
		player_->SetVelocityX(player_->GetVelocityX() + vInput.x * acceleration);
		// 速さが上限を超えないようにする
		if (fabsf(player_->GetVelocityX()) > maxSpeed)
		{
			player_->SetVelocityX(maxSpeed * (player_->GetVelocityX()) / (fabsf(player_->GetVelocityX())));
		}
	}



}

// 速度を用いて平行移動させる
void PlayerMoveComponent::Translate(Vector2f vMove)
{
	// タイルのサイズ
	float TileSize = GetMap()->GetTileSize();
	// プレイヤーのタイルとの衝突幅・高さ
	float CollisionSize = 40.0f;
	// コリジョンサイズの半分をよく使うので変数にしておく
	float CollisionSizeHalf = CollisionSize / 2.0f;

	// x軸方向の移動処理
	if (player_->GetVelocityX() != 0.0f)
	{
		// 現在位置に移動ベクトルのx成分を足して移動先の位置とする
		Vector2f vTargetPos = player_->GetPosition() + Vector2f(player_->GetVelocityX(), 0.0f);
		// 壁との衝突チェック
		if (!GetMap()->IsInsideWall(vTargetPos, CollisionSize, CollisionSize))
		{
			// 壁に衝突しないのであれば現在位置にそのまま移動先座標を適用してよい
			player_->SetPosition(vTargetPos);
		}
		else
		{
			// 壁に衝突する場合の処理

			// 右向きに移動しようとしていた場合
			if (player_->GetVelocityX() > 0.0f)
			{
				// 衝突したタイルの列数を算出
				int col = (int)((vTargetPos.x + CollisionSizeHalf) / TileSize);
				// 衝突したタイルの左端のx座標を作る
				float tile_left = (float)col * TileSize;
				// 衝突したタイルの左端と接するようにプレイヤーの位置を調整する
				player_->SetPositionX(tile_left - CollisionSizeHalf);
			}
			// 左向きに移動しようとしていた場合
			if (player_->GetVelocityX() < 0.0f)
			{
				// 衝突したタイルの列数を算出
				int col = (int)((vTargetPos.x - CollisionSizeHalf) / TileSize);
				// 衝突したタイルの右端のx座標を作って
				float tile_right = (float)col * TileSize + TileSize;
				// 衝突したタイルの右端に接するようにプレイヤーの位置を調整する
				player_->SetPositionX(tile_right + CollisionSizeHalf);
			}
		}
	}

	// Y軸方向の移動処理
	if (player_->GetVelocityY() != 0.0f)
	{
		// 現在位置に移動ベクトルのy成分を足して移動先の位置とする
		Vector2f vTargetPos = player_->GetPosition() + Vector2f(0.0f, player_->GetVelocityY());
		// 壁との衝突チェック
		if (!GetMap()->IsInsideWall(vTargetPos, CollisionSize, CollisionSize))
		{
			// 壁に衝突しないのであれば現在位置にそのまま移動先座標を適用
			player_->SetPosition(vTargetPos);
		}
		else
		{
			// 上向きに移動しようとしていた場合
			if (player_->GetVelocityY() > 0.0f)
			{
				// 衝突したタイルの行数を算出
				int row = (int)((vTargetPos.y + CollisionSizeHalf) / TileSize);
				// 衝突したタイルの下端のy座標を作って
				float wall_buttom = (float)row * TileSize - TileSize;
				// 衝突したタイルの下端に接するようにプレイヤーの位置を調整する
				player_->SetPositionY(wall_buttom - CollisionSizeHalf);
			}
			// 下向きに移動しようとしていた場合
			if (player_->GetVelocityY() < 0.0f)
			{
				// 衝突したタイルの行数を算出
				int row = (int)((vTargetPos.y - CollisionSizeHalf) / TileSize);
				// 衝突したタイルの上端のy座標を作って
				float wall_top = (float)row * TileSize;
				// 衝突したタイルの上端に接するようにプレイヤーの位置を調整する
				player_->SetPositionY(wall_top + CollisionSizeHalf);
			}
		}
	}
}

void PlayerMoveComponent::Reset()
{
	behaviourFlagTable_ = defaultBehaviourFlagTable_;
	moveInput = { 0.0f,0.0f };
}

void PlayerMoveComponent::InitializeDefaults()
{

}

bool PlayerMoveComponent::GroundCheck(const Vector2f& _position)
{
	// 衝突判定用の矩形の中心点を自分の足元にする
	Lib::Math::Vector2f vTargetPos = _position + Lib::Math::Vector2f(0.0f, -20.0f);
	// 衝突判定用の矩形の幅と高さ
	float CollisionWidth = 40.0f;
	float CollisionHeight = 1.0f;
	// 壁に衝突していたら地面に立っている
	return GetMap()->IsInsideWall(vTargetPos, CollisionWidth, CollisionHeight);
}

PlayerMoveComponent::PlayerMoveComponent(bool _isActive, Player* _player, Messenger* _messenger) : Component(_isActive), player_(_player), messenger_(_messenger)
{
	InitializeDefaults();
}

PlayerMoveComponent::PlayerMoveComponent(Player* _player, Messenger* _messenger) :player_(_player), messenger_(_messenger)
{
	InitializeDefaults();
}

void PlayerMoveComponent::UpdateDirection(const Vector2f _moveInput)
{
	if (_moveInput.GetLength() != 0.0f)
	{
		if (fabsf(_moveInput.x) > fabsf(_moveInput.y))
		{
			// 移動ベクトルのx成分がy成分より大きい場合
			// 移動ベクトルのx成分が負数であれば左向き、でなければ右向き
			player_->SetDirection((_moveInput.x < 0.0f) ? Direction::Left : Direction::Right);
		}
		else
		{
			// 移動ベクトルのy成分がx成分より大きい場合
			// 移動ベクトルのy成分が負数であれば左向き、でなければ右向き
			player_->SetDirection((_moveInput.y < 0.0f) ? Direction::Front : Direction::Back);
		}
	}
}

void PlayerMoveComponent::Init()
{
	Component::Init();
	moveInput = { 0.0f,0.0f };

	// 位置の初期化
	player_->SetPosition(96.0f, -96.0f);

	// 速度の初期化
	player_->SetVelocity(0.0f, 0.0f);

	Reset();
}

void PlayerMoveComponent::SendTranslateAnimationRequest(const Vector2f& _moveInput, const Direction& _direction)
{
	// アイドル時のアニメーションID
	const int animID_idle[] = {
		static_cast<int>(AnimationType::IDLE_FRONT),
		static_cast<int>(AnimationType::IDLE_RIGHT),
		static_cast<int>(AnimationType::IDLE_BACK),
		static_cast<int>(AnimationType::IDLE_LEFT)
	};

	// 歩行時のアニメーションID
	const int animID_walk[] = {
		static_cast<int>(AnimationType::WALK_FRONT),
		static_cast<int>(AnimationType::WALK_RIGHT),
		static_cast<int>(AnimationType::WALK_BACK),
		static_cast<int>(AnimationType::WALK_LEFT)
	};

	// 再生するアニメーションID
	int playAnimID;
	if (_moveInput.GetLength() == 0.0f)
	{
		// 移動ベクトルの長さがゼロ＝移動していない
		// 向きに応じたアイドル時のアニメを選択
		playAnimID = animID_idle[(int)_direction];
	}
	else
	{
		// 移動ベクトルがゼロでない＝移動している
		// 向きに応じた歩行時のアニメを選択
		playAnimID = animID_walk[(int)_direction];
	}

	AnimationMessage::AnimationMessageParams params = {
		playAnimID,
		AnimationPlayStyle::Continue,
	};
	AnimationMessage animationMessage(params);
	messenger_->SendMSG(animationMessage);
}

void PlayerMoveComponent::Update()
{
	Component::Update();



	if (GetFlag(PlayerStateComponent::BehaviourType::START_JUMP) && GroundCheck(player_->GetPosition()))
	{
		// 加速度のY成分を+方向に設定
		player_->SetVelocityY(20.0f);
		// ジャンプ音を再生
	}

	if (GetFlag(PlayerStateComponent::BehaviourType::START_MOVE))
	{
		// 速度を更新する
		UpdateVelocity(moveInput);

		// 向きを更新
		UpdateDirection(moveInput);

	}

	if (GetFlag(PlayerStateComponent::BehaviourType::RELEASE_JUMP) && player_->GetVelocityY() > 0.0f)
	{
		player_->SetVelocityY(player_->GetVelocityY() * 0.5f);
	}


	// 速度を用いて平行移動させる
	Translate(player_->GetVelocity());
	SendTranslateAnimationRequest(moveInput, player_->GetDirection());

	Reset();
}

void PlayerMoveComponent::HandleMessage(const IEventMessage& _msg)
{
	if (_msg.GetMessageType() ==IEventMessage::MessageType::BEHAVIOUR)
	{
		const BehaviourMessage* behaviourMsg = TypeidSystem::SafeCast<BehaviourMessage>(&_msg);

		if (!behaviourMsg)
			return;

		BehaviourMessage::BehaviourMessageParams params = behaviourMsg->GetMoveParams();

		if (params.behaviourType_ == PlayerStateComponent::BehaviourType::START_MOVE)
		{
			moveInput = behaviourMsg->GetMoveParams().moveInput;
			SetFlag(PlayerStateComponent::BehaviourType::START_MOVE, true);
		}

		if (params.behaviourType_ == PlayerStateComponent::BehaviourType::START_JUMP)
		{
			SetFlag(PlayerStateComponent::BehaviourType::START_JUMP, true);
		}

		if (params.behaviourType_ == PlayerStateComponent::BehaviourType::RELEASE_JUMP)
		{
			SetFlag(PlayerStateComponent::BehaviourType::RELEASE_JUMP, true);
		}
	}
}
