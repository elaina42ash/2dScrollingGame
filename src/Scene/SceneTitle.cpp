#include "Scene/SceneTitle.h"
#include "Fwk/Framework.h"
#include "AppDef.h"
#include "GamePlayData/GamePlayData.h"

SceneTitle::SceneTitle(int _sceneIndex): Scene(_sceneIndex)
{

}

// 初期化
void SceneTitle::Init() {
	// "次のシーン"の初期値を"なし"にしておく
	mNextScene = SceneType::None;

	// カメラの位置のリセット
	Camera camera;
	camera.SetPosition(0.0f, 0.0f);
	RenderManager_I->SetCamera(camera);

	// テクスチャの読み込み
	mTexture.Load("Images/2dAction/title.png");

	// スプライトの初期化
	mSprite.Init();
	// テクスチャの設定
	mSprite.SetTexture(mTexture);
	// スプライトのサイズ設定
	mSprite.SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	// テクスチャの描画範囲を指定
	mSprite.SetTexCoord(0.0f, 0.0f, 1.0f, 1.0f);

	mPosition = {0.0f,0.0f };

}

// 終了
void SceneTitle::Term()
{
	mSprite.Term();
	mTexture.Unload();
}

// 更新
void SceneTitle::Update() {

	// Aボタンを押したら"次のシーン"にステージ選択シーンを設定する
	if (Input_I->IsKeyDown('Z')||Input_I->IsButtonDown(0,GAMEPAD_BUTTON::A))
	{

		GetGamePlayData().SetStageNo(0);

		mNextScene = SceneType::Introduction;
	}
}

// 描画
void SceneTitle::Render()
{
	mSprite.Draw();

	//// 文字列を描画する
	//PrintText("アクションゲーム！",380.0f,250.0f);
}


