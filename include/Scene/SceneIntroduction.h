#pragma once
#include "Scene.h"
#include "Fwk/Framework.h"
#include "GamePlayData/GamePlayData.h"
#include "Lib/System/GamePad.h"

class SceneIntroduction : public Scene {
public:
	SceneIntroduction() = default;

	explicit SceneIntroduction(int _sceneIndex);

	// 初期化
	void Init();
	// 終了
	void Term();
	// 更新
	void Update();
	// 描画
	void Render();

private:
};
