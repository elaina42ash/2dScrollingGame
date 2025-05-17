#pragma once

//（敵）鬼火クラス

#include "Enemy.h"

class Onibi : public Enemy {
public:
	// 初期化
	void Init() override;
	// 更新
	void Update() override;

	void Term() override;
	// 生成された時に呼び出される
	void OnCreated() override;

	void HandleMessage(const IEventMessage& _msg) override;

private:

	// アニメーションの初期化
	void _initAnimation();
};