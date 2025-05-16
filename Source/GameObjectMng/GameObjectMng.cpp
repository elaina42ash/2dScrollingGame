#include "GameObjectMng.h"

#include "Enemy/EnemyMng.h"

#include "Goal/Goal.h"

// ステージ情報構造体
#include "Mst/StageData.h"

// 画面サイズの定数を使うのでinclude
#include "AppDef.h"

// CSVファイルの読み込み
#include "Fwk/File/CSVFile.h"

// Key-Valueファイルの読み込み
#include "Fwk/File/KeyValueFile.h"

// RenderMangerを使うのでiinclude
#include "Fwk/Framework.h"

// UIMngを使うのでinclude
#include "Mst/StageDataMst.h"
#include "UI/UIMng.h"

Tilemap mMap;
Player* player_;
EnemyMng* enemyMng_;
UIMng mUIMng;
Goal* goal_;


Player* GetPlayer()
{
	return player_;
}

void ResetPlayer()
{
	if (player_)
	{
		delete player_;
		player_ = nullptr;
	}

	player_ = new Player;
}

// 全オブジェクト初期化
void GameObjectInit(StageData* pStageData)
{
	mMap.Init();

	if (!player_)
	{
		player_ = new Player;
	}

	if (player_&& pStageData== GetStageDataMst().Get(0))
		player_->Init();

	if (player_ && pStageData != GetStageDataMst().Get(0))
	{
		player_->ResetPlayer();
	}

	if (!enemyMng_)
	{
		enemyMng_ = new EnemyMng;
	}
	enemyMng_->Init();
	// スライムのオブジェクトプールを確保
	enemyMng_->GeneratePool("Slime", 10);
	// 鬼火のオブジェクトプールを確保
	enemyMng_->GeneratePool("Onibi", 10);
	// 幽霊のオブジェクトプールを確保
	enemyMng_->GeneratePool("Ghost", 10);
	// がいこつのオブジェクトプールを確保
	enemyMng_->GeneratePool("Skull", 10);

	// 敵の配置情報をファイルから取得する
	if (pStageData)
	{
		CSVFile csvFile;
		csvFile.Load(pStageData->ArrangementFile);
		// 読み込みだCSVファイル内容をコンソールに出力する(デバッグ用)
		csvFile.PrintCSVData();
		// CSVデータから敵を配置する
		if (enemyMng_)
			enemyMng_->CreateEnemies(csvFile.GetCSVData());
		
	}
	// マップデータをファイルから取得する
	if (pStageData)
	{
		KeyValueFile mapdataFile;
		mapdataFile.Load(pStageData->MapFile);
		// マップの列数を取得
		int col = mapdataFile.GetInt("Col");
		// マップの行数を取得
		int row = mapdataFile.GetInt("Row");
		// CSVDataからマップを生成する
		mMap.CreateMap(col, row, mapdataFile.GetCSVData("Data"));

		// ゴールを配置
		if (!goal_)
		{
			goal_ = new Goal;
		}
		goal_->Init();
		CSVData* pCSV = mapdataFile.GetCSVData("Goal");
		if (pCSV != nullptr)
		{
			float x = pCSV->GetFloat(0);
			float y = pCSV->GetFloat(1);
			goal_->SetPosition(Vector2f(x, y));
		}
		// プレイヤーの位置を設定
		CSVData* pStartPos = mapdataFile.GetCSVData("Start");
		if (pStartPos != nullptr)
		{
			float x = pStartPos->GetFloat(0);
			float y = pStartPos->GetFloat(1);

			Vector2f initialPosition = { x,y };

			if (player_)
			{
				auto* transform = player_->GetComponent<ITransformComponent>();
				if (transform)
					transform->MoveTo(initialPosition);
			}

		}
	}

	// UIマネージャの初期化
	mUIMng.Init();
}

// 全オブジェクト更新
void GameObjectUpdate()
{
	// 最初にプレイヤーの更新
	if (player_)
		player_->Update();


	if (player_ && player_->IsAlive())
	{
		// プレイヤーの現在位置にカメラの位置を合わせる
		Vector2f cameraPosition = { 0.0f,0.0f };
		if (player_)
		{
			cameraPosition = player_->GetPosition();
		}

		// マップ全体のサイズを取得
		Vector2f mapSize = mMap.GetMapSize();

		// カメラの移動可能範囲を作る
		float cameraArea_left = WINDOW_WIDTH / 2.0f; // 左端
		float cameraArea_top = -WINDOW_HEIGHT / 2.0f; // 右端
		float cameraArea_right = mapSize.x - WINDOW_WIDTH / 2.0f; // 上端
		float cameraArea_bottom = -mapSize.y + WINDOW_HEIGHT / 2.0f; // 下端

		// カメラ位置がカメラの移動範囲内に収めるように調整
		if (cameraPosition.x < cameraArea_left)
		{
			cameraPosition.x = cameraArea_left;
		}
		if (cameraPosition.x > cameraArea_right)
		{
			cameraPosition.x = cameraArea_right;
		}
		if (cameraPosition.y > cameraArea_top)
		{
			cameraPosition.y = cameraArea_top;
		}
		if (cameraPosition.y < cameraArea_bottom)
		{
			cameraPosition.y = cameraArea_bottom;
		}

		// カメラの位置を更新
		Camera camera;
		camera.SetPosition(cameraPosition);
		RenderManager_I->SetCamera(camera);
	}

	mMap.Update();

	if (enemyMng_)
		enemyMng_->Update();

	//mOnibi.Update();

	// ゴール地点を更新
	if (goal_)
		goal_->Update();
	

	// プレイヤーの体力をUIマネージャに渡す
	if (player_)
	{
		mUIMng.SetHp(player_->GetHp());
		mUIMng.SetHp(player_->GetNormalizedHp());
	}

	// UIマネージャの更新
	mUIMng.Update();
}

// 全オブジェクト描画
void GameObjectRender()
{
	mMap.Render();

	if (player_)
		player_->Render();

	if (enemyMng_)
		enemyMng_->Render();
	

	// ゴール地点を描画
	if (goal_)
		goal_->Render();


	// UIマネージャの描画
	mUIMng.Render();
}

// 全オブジェクト解放
void GameObjectTerm()
{
	mMap.Term();

	if (player_)
	{
		player_->Term();
		delete player_;
		player_ = nullptr;
	}

	if (enemyMng_)
	{
		enemyMng_->Term();
		delete enemyMng_;
		enemyMng_ = nullptr;
	}
	

	// ゴール地点を解除
	if (goal_)
	{
		goal_->Term();
		delete goal_;
		goal_ = nullptr;
	}
		


	// UIマネージャの解放
	mUIMng.Term();
}

Tilemap* GetMap()
{
	return &mMap;
}

// 敵マネージャクラスのポインタを返す
EnemyMng* GetEnemyMng()
{
	return enemyMng_;
}


