#include "SceneStageSelect.h"
// ゲームプレイデータを使う
#include "GameObjectMng/GameObjectMng.h"

// 初期化
void SceneStageSelect::Init()
{
	Scene::Init();
}

// 終了
void SceneStageSelect::Term()
{
	// なし
}

// 更新
void SceneStageSelect::Update()
{
	// 次のシーンをゲームクリアシーンにする
	mNextScene = SceneType::InGame;
}

// 描画
void SceneStageSelect::Render()
{
	
}
