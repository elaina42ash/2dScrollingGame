#include "SceneInGame.h"


#include "GameObjectMng/GameObjectMng.h"

// ゲームプレイデータ
#include "GamePlayData/GamePlayData.h"
// ステージ情報マスタ
#include "Mst/StageDataMst.h"
#include "World/World.h"

// 初期化
void SceneInGame::Init()
{
	Scene::Init();

	// 遊ぶステージの番号を取得
	int stageNo = GetGamePlayData().GetStageNo();
	// 遊ぶステージの情報を取得
	StageData* pStageData = GetStageDataMst().Get(0);

	// ゲームオブジェクトの初期化
	gameObjectMng_.Init(pStageData);

	
	// BGMファイルの読み込み
	mSound.Load(BGM_URL);
	// 音源の初期化
	mSoundSource.Init(mSound);
	// BGMを繰り返し再生
	mSoundSource.Play(-1);

	WORLD_I.LoadSceneUI(SceneType::InGame);

	// "次のシーン"の初期値を"なし"にしておく
	mNextScene = SceneType::None;
}

// 終了
void SceneInGame::Term()
{
	Scene::Term();

	// ゲームオブジェクトの解放
	gameObjectMng_.Term();

	// BGMを停止
	mSoundSource.Stop();
	// 音源を解放
	mSoundSource.Term();
	// 読み込んだ音声ファイルを破棄
	mSound.Unload();

	WORLD_I.UnloadSceneUI();
}

// 更新
void SceneInGame::Update()
{
	Scene::Update();

	// ゲームオブジェクトの更新
	gameObjectMng_.Update();

	// プレイヤーを取得
	Player* player = WORLD_I.AccessMainPlayer();

	if (player)
	{
 		if (player->IsStageCleared())
		{
			needReload_ = true;
		}
		if (player->IsDead())
		{
			// 次のシーンをゲームクリアシーンにする
			mNextScene = SceneType::GameOver;
		}
	}
}

// 描画
void SceneInGame::Render()
{
	Scene::Render();

	// ゲームオブジェクトの描画
	gameObjectMng_.Render();

}

