#pragma once
#include <string>
#include "EnemyPool.h"
#include "Enemy/Enemy.h"
#include "Fwk/Data/CSVData.h"

// 敵管理クラス
class EnemyMng {
public:
	// 初期化
	void Init();
	// 後片付け
	void Term();
	// 更新
	void Update();
	// 描画
	void Render();

	// オブジェクトループの生成
	void GeneratePool(std::string _enemyName, int _poolSize);
	// 指定した敵のオブジェクトループの解放
	void DestroyPool(const char* _enemyName);
	// 全ての敵のオブジェクトループの解放
	void DestroyPoolAll();

	// 敵の生成
	Enemy* CreateEnemy(const char* _enemyName, Lib::Math::Vector2f _position, ISceneContext* _sceneContext, ISceneGameplayAPI* _sceneGameplayAPI);
	// CSVデータから敵を生成する
	void CreateEnemies(CSVData* _csvData, int _tileSize, ISceneContext* _sceneContext, ISceneGameplayAPI* _sceneGameplayAPI);
	// 残りの敵の数
	int GetEnemyCount();

private:
	// アクティブな敵オブジェクトのポインタ配列
	vector<Enemy*> mActiveEnemies;
	// 敵種別ごとのオブジェクトプール
	map<string, EnemyPool> mEnemyPools;
};