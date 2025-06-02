#pragma once

// Sceneクラスを継承するので#include
#include "Scene.h"

// ステージ選択シーンクラス
class SceneStageSelect :public Scene {
public:
	SceneStageSelect() = default;

	explicit SceneStageSelect(int _sceneIndex);

	// 初期化
	void Init();
	// 終了
	void Term();
	// 更新
	void Update();
	// 描画
	void Render();
};