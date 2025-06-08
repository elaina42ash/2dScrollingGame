#include "Scene/SceneIntroduction.h"

void SceneIntroduction::Init()
{
	Scene::Init();
}

void SceneIntroduction::Term()
{
	Scene::Term();
}

void SceneIntroduction::Update()
{
	Scene::Update();
	// Aボタンを押したら"次のシーン"にステージ選択シーンを設定する
	if (Input_I->IsKeyDown('Z') || Input_I->IsButtonDown(0, GAMEPAD_BUTTON::A))
	{

		GetGamePlayData().SetStageNo(0);

		mNextScene = SceneType::InGame;
	}
}

void SceneIntroduction::Render()
{
	Scene::Render();

	PrintText("操作説明", 350.0f, 150.0f);	
	PrintText("Space：ジャンプ", 350.0f, 200.0f);	
	PrintText("E：武器を変更する", 350.0f, 250.0f);	
	PrintText("G：武器を捨てる", 350.0f, 300.0f);	
	PrintText("J：攻撃", 350.0f, 350.0f);	
	PrintText("L：ダッシュ", 350.0f, 400.0f);	
	PrintText("K：インタラクト", 350.0f, 450.0f);	

}
