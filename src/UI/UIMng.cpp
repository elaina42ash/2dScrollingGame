#include "UI/UIMng.h"

#include "UI/HpGauge.h"
#include "UI/HpGauge2.h"
#include "World/World.h"

void UIMng::InitGlobalUI()
{
	for (auto* ui : globalUIs_)
		ui->Init();
}

void UIMng::LoadSceneUI(SceneType type)
{
	switch (type)
	{
	case SceneType::InGame:
	{
		HpGauge2* hpGauge2 = new HpGauge2;
		Player* player = WORLD_I.AccessMainPlayer();
		if (player)
			hpGauge2->BindToPlayer(player);
		sceneUIs_.push_back(hpGauge2);
	}break;
	}

	for (auto* ui : sceneUIs_)
		ui->Init();
}

void UIMng::UnloadSceneUI()
{
	for (auto* ui : sceneUIs_)
	{
		ui->Term();
		delete ui;
	}
	sceneUIs_.clear();
}

// 更新
void UIMng::Update()
{
	for (auto* ui : globalUIs_)
		ui->Update();

	for (auto* ui : sceneUIs_)
		ui->Update();
}

// 描画
void UIMng::Render()
{
	for (auto* ui : globalUIs_)
		ui->Render();

	for (auto* ui : sceneUIs_)
		ui->Render();
}




