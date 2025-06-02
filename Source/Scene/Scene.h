#pragma once
// シーン種別の列挙型を使うので#include
#include "GameDef.h"


// シーンクラス
class Scene {
public:
	Scene() = default;

	explicit Scene(int _sceneIndex);

	// 初期化
	virtual void Init();
	// 終了
	virtual void Term();
	// 更新
	virtual void Update();
	// 描画
	virtual void Render();
	// 次のシーンを取得する
	SceneType GetNextScene();

	bool NeedReload() const;

	int GetSceneIndex() const;

protected:
	// 次のシーン
	SceneType mNextScene;

	int sceneIndex_ = 0;

	bool needReload_ = false;
};