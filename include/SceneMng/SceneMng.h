#pragma once
#include "GameDef.h"
#include "Scene/Scene.h"

// シーン管理クラス
class SceneMng
{
public:
	// 初期化(最初に動かすシーンを指定できるようにしておく)
	void Init(SceneType startScene);
	// 終了
	void Term();
	// 更新
	void Update();
	// 描画
	void Render();

	Scene* AccessCurrentScene()
	{
		return scene_;
	}
private:
	// 新しいシーンを開始する
	void _beginScene(SceneType newScene);
	// 現在のシーンを終了する
	void _endCurrentScene();

private:
	// 現在のシーン
	SceneType currentScene_;
	// 次のシーン
	SceneType nextScene_;

	// 現在動いているシーンクラスの変数のポインタ
	Scene* scene_;

};