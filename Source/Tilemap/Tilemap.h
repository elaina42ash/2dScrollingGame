#pragma once

// SpriteとTextureを使う為のヘッダファイル
#include <Fwk/Graphics.h>

// Vector2fを使う為のヘッダファイル
#include "Lib/Math/Vector.h"

// CSVデータを使う為にinclude
#include "Fwk/File/CSVFile.h"

class Tilemap
{
public:

	// 初期化
	void Init();
	// 終了
	void Term();
	// 更新
	void Update();
	// 描画
	void Render();
	// タイルサイズを取得
	float GetTileSize();
	// 指定した矩形の内側に壁が入り込んでいるかを戻す
	bool IsInsideWallRect(Vector2f _position,float _width,float _height) const;
	bool IsInsideWallCircle(Vector2f _position, float _radius) const;
	// サイズを指定してマップを生成する
	void CreateMap(int colNum,int rowNum,CSVData* pMapdata);
	// マップをCSVDataから生成する
	/*void CreateMap(CSVData* pMapdata);*/
	// マップ全体のサイズを取得する
	Vector2f GetMapSize() const;
private:

	// 定数。C言語のenumは型名なしで列挙ができる
	// 画面一枚を描画する為に必要なタイル（スプライト）の列数・行数
	enum {
		RENDER_COL_NUM=16+1,
		RENDER_ROW_NUM=12+1
	};
	// マップデータのサイズ
	enum 
	{
		COL_NUM=32, // 列数（ｘ軸方向ののタイル枚数）
		ROW_NUM=24, // 行数（ｙ軸方向ののタイル枚数）
	};

private:
	int mColNum;
	int mRowNum;

	// タイルパターンの画像を読み込む為のテクスチャ
	Texture mTexture;

	// 列数X行数分のスプライト
	Sprite mSprite[RENDER_ROW_NUM][RENDER_COL_NUM];

private:
	// 指定された列・行が壁であるか否かを戻す
	bool IsWall(int _col,int _row) const;
	
	// マップデータを消去する
	void _clearMapData();

	// マップデータ（タイルID）を収める配列のアドレス
	int** mpMapData;
};
