#pragma once

// SpriteとTextureを使う為のヘッダファイル
#include <Fwk/Graphics.h>

// Vector2fを使う為のヘッダファイル
#include "Lib/Math/Vector.h"

// CSVデータを使う為にinclude
#include "Fwk/File/CSVFile.h"

class Tilemap
{
private:
	enum class TileType
	{
		NONE = -1,

		WALL_FIRST = 1,
		WALL_LEFT_TOP = WALL_FIRST,
		WALL_MID_TOP,
		WALL_RIGHT_TOP,
		WALL_LEFT_MID,
		WALL_MID_MID,
		WALL_RIGHT_MID,
		WALL_LEFT_BOTTOM,
		WALL_MID_BOTTOM,
		WALL_RIGHT_BOTTOM,
		WALL_END = WALL_RIGHT_BOTTOM,

		PLATFORM_FIRST,
		PLATFORM_LEFT_TOP = PLATFORM_FIRST,
		PLATFORM_MID_TOP,
		PLATFORM_RIGHT_TOP,
		PLATFORM_LEFT_MID,
		PLATFORM_MID_MID,
		PLATFORM_RIGHT_MID,
		PLATFORM_LEFT_BOTTOM,
		PLATFORM_MID_BOTTOM,
		PLATFORM_RIGHT_BOTTOM,
		PLATFORM_END = PLATFORM_RIGHT_BOTTOM,

		BACKGROUND_FIRST,
		BACKGROUND_1 = BACKGROUND_FIRST,
		BACKGROUND_2 ,
		BACKGROUND_3 ,
		BACKGROUND_4 ,
		BACKGROUND_5 ,
		BACKGROUND_6 ,
		BACKGROUND_7 ,
		BACKGROUND_8 ,
		BACKGROUND_END = BACKGROUND_8,

	};

	const char* SOURCE_TILE_FILE_URL = "Images/2dAction/My_tiles.png";
	const float SOURCE_TILE_SIZE = 16.0f;
	const float SOURCE_TILE_FILE_MAX_SIZE = 256.0f;
	// 定数　タイル1枚分のSpriteのサイズ
	const float TileSize = 32.0f;

private:
	int colNum_ =0;
	int rowNum_ =0;

	int render_col_num = 0;
	int render_row_num = 0;

	// タイルパターンの画像を読み込む為のテクスチャ
	Texture texture_;

	// 列数X行数分のスプライト
	Sprite** sprite_ =nullptr;

	// マップデータ（タイルID）を収める配列のアドレス
	int** mapData_ = nullptr;
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
	bool IsInsideWallRect(Vector2f _position, float _width, float _height) const;
	bool IsInsideWallCircle(Vector2f _position, float _radius) const;
	// サイズを指定してマップを生成する
	void CreateMap(int colNum, int rowNum, CSVData* pMapdata);
	// マップをCSVDataから生成する
	/*void CreateMap(CSVData* pMapdata);*/
	// マップ全体のサイズを取得する
	Vector2f GetMapSize() const;

	void CreateRenderMap(int _col, int _row);

private:
	// 指定された列・行が壁であるか否かを戻す
	bool IsBlockedTile(int _col, int _row) const;

	// マップデータを消去する
	void ClearMapData();
};
