#pragma once
#include <string>
#include "Enemy.h"
#include "EnemyPool.h"
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
	void GeneratePool(std::string _enemyName, int _poolSize, IEnvironmentQuery* _environmentQuery);
	// 指定した敵のオブジェクトループの解放
	void DestroyPool(std::string enemyName);
	// 全ての敵のオブジェクトループの解放
	void DestroyPoolAll();

	// 敵の生成
	Enemy* CreateEnemy(string enemyName, Vector2f position);
	// CSVデータから敵を生成する
	void CreateEnemies(CSVData* pCsvData, int _tileSize);
	// 残りの敵の数
	int GetEnemyCount();

private:
	// アクティブな敵オブジェクトのポインタ配列
	vector<Enemy*> mActiveEnemies;
	// 敵種別ごとのオブジェクトプール
	map<string, EnemyPool> mEnemyPools;
};