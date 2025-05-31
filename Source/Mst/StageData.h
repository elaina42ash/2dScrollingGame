#pragma once

#include <string>
using namespace std;

// ステージ情報構造体
struct StageData
{
	string stageName_; // ステージ名
	string mapFile_; // マップデータファイル名
	string enemyArrangementFile_; // 配置データファイル名
	string staticObjectArrangementFile_; // 配置データファイル名
};