#include "App.h"

#include "GameObjectMng/GameObjectMng.h"

#include "Scene/SceneMng.h"
#include "GamePlayData/GamePlayData.h"
#include "Mst/StageDataMst.h"

SceneMng sceneMng;

Tilemap tilemap;

//---------------------------------------------------------
//ゲームの初期化処理を行う関数
//---------------------------------------------------------
void App::Init() {
	// UI用の描画レイヤーを追加する
	RenderManager_I->AddLayer("UI");

	// 画面の左上がゲーム空間の原点（0，0）となるにカメラを移動する
	{
		Camera camera;
		camera.SetPosition(WINDOW_WIDTH / 2.0f, -WINDOW_HEIGHT / 2.0f);
		RenderManager_I->SetCamera(camera);
	}

	// UIレイヤー用のカメラの追加・設定
	{
		Camera camera;
		// カメラ名を指定する
		camera.SetName("UI");
		// 映す対象のレイヤーに"UI"を追加
		camera.AddRenderLayer("UI");
		// "UI"カメラをアクティブにする
		camera.SetActive(true);
		// カメラの位置を調整
		camera.SetPosition(WINDOW_WIDTH/2.0f,-WINDOW_HEIGHT/2.0f);
		// UI用のカメラの設定を更新
		RenderManager_I->SetCamera(camera);
	}

	// ゲームプレイデータを初期化する
	GetGamePlayData().Init();
	// ステージ情報マスタを初期化する
	GetStageDataMst().Init();

	// シーン管理クラスを初期化、最初のシーンをタイトルシーン
	sceneMng.Init(SceneType::Title);
}
//---------------------------------------------------------
//ゲームの更新処理を行う関数
//---------------------------------------------------------
void App::Update() {
	// シーン更新
	sceneMng.Update();
}

//---------------------------------------------------------
//ゲームの描画処理を行う関数
//---------------------------------------------------------
void App::Render() {
	// シーン描画
	sceneMng.Render();
}
//---------------------------------------------------------
// ゲームの後片付け処理を行う関数
//---------------------------------------------------------
void App::Term() {
	// シーン解放
	sceneMng.Term();
}
