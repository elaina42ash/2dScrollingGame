#pragma once

// SpriteヤTexture,Animationを使うためのヘッダファイル
#include "Fwk/Graphics.h"

// Vector2fクラスを使うためのヘッダファイル
#include "Lib/Math/Vector.h"
using namespace Lib::Math;

// コリジョンクラスを使うのでinclude
#include "Fwk/Collision/Collider.h"

// コリジョンクラスの名前空間を使う
using namespace Fwk::Collision;

// ゴール地点クラス
class Goal {
public:
	// 初期化
	void Init();
	// 終了
	void Term();
	// 更新
	void Update();
	// 描画
	void Render();

	// 位置設定
	void SetPosition(Vector2f position);

private:
	Texture mTexture;
	Sprite mSprite;
	Collider mCollision;
};