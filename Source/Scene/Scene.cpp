#include "Scene.h"

#include "Fwk/Framework.h"

Scene::Scene(int _sceneIndex): sceneIndex_(_sceneIndex)
{
}

// 初期化
void Scene::Init()
{
	// "次のシーン"の初期値を"なし"にしておく
	mNextScene = SceneType::None;
}

// 終了
void Scene::Term()
{
	// なし
}

// 更新
void Scene::Update()
{
	// なし
}

// 描画
void Scene::Render()
{
	// なし
}

// 次のシーンを取得する
SceneType Scene::GetNextScene()
{
	return mNextScene;
}

bool Scene::NeedReload() const
{
	return needReload_;
}

int Scene::GetSceneIndex() const
{
	return sceneIndex_;
}


