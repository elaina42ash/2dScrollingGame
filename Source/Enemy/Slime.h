#pragma once

// （敵）スライムクラス

// 親クラス
#include "Enemy.h"

// Directionの定数を使いたいので#include
#include "GameDef.h"

class Slime : public Enemy {


private:
	// 敵の状態
	enum class Status {
		Falling, // 下落中
		Moving, // 水平移動中
	};

public:
	// 初期化
	void Init() override;
	// 更新
	void Update() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

private:
	// 落下時の処理
	void _updateFalling();
	// 移動時の処理
	void _updateMoving();

private:
	// 状態
	Status mStatus;
	// 加速度


private:
	Vector2f mVelocity;
	// 水平移動時の向き
	Direction mDirection;
};