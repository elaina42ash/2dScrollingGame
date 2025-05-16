#pragma once

// タイルマップ
#include "Tilemap/Tilemap.h"
// 敵マネージャ
#include "Enemy/EnemyMng.h"
// ステージ情報構造体
#include "Mst/StageData.h"

#include "Player/Player.h"

// プレイヤークラスのポインタをかえす
Player* GetPlayer();

void ResetPlayer();

// 全オブジェクト初期化
void GameObjectInit(StageData* pStageData);

// 全オブジェクト更新
void GameObjectUpdate();

// 全オブジェクト描画
void GameObjectRender();

// 全オブジェクト解放
void GameObjectTerm();

// Tilemapクラスのアドレスを返す
Tilemap* GetMap();

// 敵マネージャクラスのポインタを返す
EnemyMng* GetEnemyMng();

