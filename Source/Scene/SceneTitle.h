#pragma once

// Sceneクラスを継承するので#include
#include "Scene.h"

// SpriteやTexture,Animationを使うためのヘッダファイル
#include "Fwk/Graphics.h"
#include "GameObject/StaticObject/IronSpike.h"

// タイトルシーンクラス
class SceneTitle : public Scene{
public:
	SceneTitle() = default;

	explicit SceneTitle(int _sceneIndex);

	// 初期化
	void Init();
	// 終了
	void Term();
	// 更新
	void Update();
	// 描画
	void Render();

private:
	Texture mTexture;
	Sprite mSprite;
	Vector2f mPosition;
	int count = 0;

};