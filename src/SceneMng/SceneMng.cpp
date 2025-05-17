#include "SceneMng/SceneMng.h"

#include "Fwk/Framework.h"
#include "Scene/SceneGameClear.h"
#include "Scene/SceneGameOver.h"
#include "Scene/SceneInGame.h"
#include "Scene/SceneStageSelect.h"
#include "Scene/SceneTitle.h"


// 初期化
void SceneMng::Init(SceneType startScene)
{
	// 現在のシーンは"なし"
	currentScene_ = SceneType::None;
	// 次に動かすシーンを記録しておく
	nextScene_ = startScene;

	// 現在のシーンクラスの変数ポインタはnullを設定しておく
	scene_ = nullptr;
}

// 終了
void SceneMng::Term()
{
	// 現在のシーンを終了する
	_endCurrentScene();
	// 次のシーンは"なし"としておく
	nextScene_ = SceneType::None;
}
// 更新
void SceneMng::Update()
{
	if (scene_ && currentScene_ != SceneType::None && scene_->NeedReload())
	{
		SceneType remainingScene = currentScene_;
		// 現在動いているシーンを止める
		_endCurrentScene();

		// 新しいシーンを開始する
		switch (remainingScene)
		{
		case SceneType::Title:
			// タイトルシーンの生成
			scene_ = new SceneTitle();
			break;
		case SceneType::InGame:
			// インゲームシーンの生成
			scene_ = new SceneInGame();
			break;
		case SceneType::GameOver:
			// ゲームオーバーシーンの生成
			scene_ = new SceneGameOver();
			break;
		case SceneType::GameClear:
			// ゲームクリアシーンの生成
			scene_ = new SceneGameClear();
			break;
		case SceneType::StageSelect: // ステージ選択シーンの生成
			scene_ = new SceneStageSelect();
			break;
		}

		Framework_I->LateUpdate();

		// 生成したシーンの初期化
		if (scene_ != nullptr)
		{
			scene_->Init();
		}

		// 現在のシーンを設定
		currentScene_ = remainingScene;

	}


	// 次のシーンを設定されており、
	// 現在のシーンがそのシーンと異なっていたらシーンを切り替える
	if (nextScene_ != SceneType::None && currentScene_ != nextScene_)
	{
		// 次のシーンを開始する
		_beginScene(nextScene_);
	}

	// 現在のシーンを更新
	if (scene_!=NULL)
	{
		scene_->Update();
		nextScene_ = scene_->GetNextScene();
	}
}

// 描画
void SceneMng::Render()
{
	// 現在のシーンを描画
	if (scene_ != nullptr)
	{
		scene_->Render();
	}
}

// 新しいシーンを開始する
void SceneMng::_beginScene(SceneType newScene)
{
	// 現在動いているシーンを止める
	_endCurrentScene();

	// 新しいシーンを開始する
	switch (newScene)
	{
	case SceneType::Title:
		// タイトルシーンの生成
		scene_ = new SceneTitle();
		break;
	case SceneType::InGame:
		// インゲームシーンの生成
		scene_ = new SceneInGame();
		break;
	case SceneType::GameOver:
		// ゲームオーバーシーンの生成
		scene_ = new SceneGameOver();
		break;
	case SceneType::GameClear:
		// ゲームクリアシーンの生成
		scene_ = new SceneGameClear();
		break;
	case SceneType::StageSelect: // ステージ選択シーンの生成
		scene_ = new SceneStageSelect();
		break;
	}

	// 生成したシーンの初期化
	if (scene_ !=nullptr)
	{
		scene_->Init();
	}

	// 現在のシーンを設定
	currentScene_ = newScene;

}

// 現在のシーンを終了する
void SceneMng::_endCurrentScene()
{
	if (scene_ !=nullptr)
	{
		scene_->Term();
		SAFE_DELETE(scene_);
	}
	// シーンを止めたので現在のシーンを"なし"にしておく
	currentScene_ = SceneType::None;
}


