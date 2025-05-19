#include "EnemyMng.h"

// SAFE_DELETEを使うために#include
#include "Lib/LibDef.h"

// 生成する敵のクラスの宣言をinclude
#include "Slime.h"
#include "Onibi.h"
#include "Ghost.h"
#include "Skull.h"

// 初期化
void EnemyMng::Init() {
	// アクティブな敵のポインタの配列を空にしておく
	mActiveEnemies.clear();
}

// 後片付け
void EnemyMng::Term() {
	// アクティブな敵のポインタの配列を空にしておく
	mActiveEnemies.clear();
	// すべての敵プールを破棄
	DestroyPoolAll();
}

// 更新
void EnemyMng::Update() {
	// アクティブな敵を全て更新する
	for (int i = 0; i < mActiveEnemies.size(); i++)
	{
		// 更新
		mActiveEnemies[i]->Update();
	}
	// アクティブな敵を全て更新する
	for (int i = 0; i < mActiveEnemies.size();)
	{
		if (mActiveEnemies[i]->IsActive())
		{
			// mActiveEnemies[i]がアクティブのままであれば
			// 次の要素を処理するのでiをインクリメント
			++i;
		}
		else
		{
			// mActiveEnemies[i]が非アクティブとなっていたらその要素を取り除く
			mActiveEnemies.erase(mActiveEnemies.begin() + i);

			// ※ここではiをインクリメントしない
		}
	}
}

// 描画
void EnemyMng::Render() {
	// アクティブな敵を全て描画
	for (int i = 0; i < mActiveEnemies.size(); i++)
	{
		// 描画
		mActiveEnemies[i]->Render();
	}
}

// オブジェクトプールの生成
void EnemyMng::GeneratePool(string _enemyName, int _poolSize, IEnvironmentQuery* _environmentQuery) {
	// スライムのプール作成
	if (_enemyName=="Slime")
	{
		// 生成する敵クラスにSlimeを指定
		mEnemyPools[_enemyName].Init<Slime>(_poolSize, _environmentQuery);
	}
	// 鬼火のプール作成
	if (_enemyName=="Onibi")
	{
		// 生成する敵クラスにOnibiを指定
		mEnemyPools[_enemyName].Init<Onibi>(_poolSize, _environmentQuery);
	}
	// 幽霊のプール作成
	if (_enemyName=="Ghost")
	{
		// 生成する敵クラスにGhostを指定
		mEnemyPools[_enemyName].Init<Ghost>(_poolSize, _environmentQuery);
	}
	// がいこつのプール作成
	if (_enemyName == "Skull")
	{
		// 生成する敵クラスにGhostを指定
		mEnemyPools[_enemyName].Init<Skull>(_poolSize, _environmentQuery);
	}
}

// 全ての敵のオブジェクトプールの廃棄
void EnemyMng::DestroyPoolAll() {
	// スライムのバッファを廃棄
	DestroyPool("Slime");
	// 鬼火のバッファを廃棄
	DestroyPool("Onibi");
	// 幽霊のバッファを廃棄
	DestroyPool("Ghost");
	// がいこつのバッファを廃棄
	DestroyPool("Skull");
}

// 指定した敵のオブジェクトプールの廃棄
void EnemyMng::DestroyPool(string enemyName) {
	// 敵のプール破棄
	if (mEnemyPools.count(enemyName)>0)
	{
		mEnemyPools[enemyName].Term();
		mEnemyPools.erase(enemyName);
	}
}

// 敵の生成
Enemy* EnemyMng::CreateEnemy(string enemyName, Vector2f position) {
	// 指定の敵プールから非アクティブのオブジェクトを取得する
	Enemy* pEnemy = nullptr;

	// 敵プールから空きオブジェクトを取得
	if (mEnemyPools.count(enemyName)>0)
	{
		pEnemy = mEnemyPools[enemyName].Alloc();
	}

	// 非アクティブの敵オブジェクトがなければ生成失敗
	if (pEnemy == nullptr)
	{
		return nullptr;
	}

	// 位置を設定
	pEnemy->SetPosition(position);

	// 生成時の関数を呼び出す
	pEnemy->OnCreated();

	// アクティブな敵配列に追加しておく
	mActiveEnemies.push_back(pEnemy);

	return pEnemy;
}

// 残りの敵の数
int EnemyMng::GetEnemyCount() {
	return (int)mActiveEnemies.size();
}

// CSVデータから敵を生成する
void EnemyMng::CreateEnemies(CSVData* pCsvData, int _tileSize) {

	// nullptrが渡されてきたら何もしないで関数を抜ける
	if (pCsvData == nullptr)
		return;

	// 敵の情報は、名前、X座標、ｙ座標の３つで１組。
	// CSVファイルの全要素を３で割って敵の配置情報の数とする
	int enemyNum = pCsvData->GetElementCount() / 3;
	// 配置する敵の数だけ繰り返し
	for (int i = 0; i < enemyNum; i++)
	{
		// 敵1体の配置データの先頭の要素番号
		int index = i * 3;
		// 敵の名前を取得
		string enemyName;
		pCsvData->GetString(index,&enemyName);

		float gridX = pCsvData->GetFloat(index + 1);
		float gridY = pCsvData->GetFloat(index + 2);

		Vector2f position;
		position.x = gridX * _tileSize;
		position.y = -gridY * _tileSize;

		// 敵を生成
		CreateEnemy(enemyName,position);
	}
}

