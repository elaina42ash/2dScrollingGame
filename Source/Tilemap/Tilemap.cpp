#include "Tilemap.h"
// RenderMangerを使うのでinclude
#include "Fwk/Framework.h"
// ウインドウサイズの定数を使うのでinclude
#include "AppDef.h"

// 定数　タイル1枚分のSpriteのサイズ
const float TileSize = 64.0f;

// 初期化
void Tilemap::Init() {
	// マップサイズを初期化
	mColNum = 0;
	mRowNum = 0;
	// マップデータを収める二次元配列のポイントを初期化
	mpMapData = nullptr;
	// テクスチャファイルの読み込む
	mTexture.Load("Images/2dAction/tiles.png");

	// スプライトの初期化と各種設定
	for (int i = 0; i < RENDER_ROW_NUM; i++)
	{
		for (int n = 0; n < RENDER_COL_NUM; n++)
		{
			// 初期化
			mSprite[i][n].Init();
			// テクスチャ設定
			mSprite[i][n].SetTexture(mTexture);
			// サイズを設定
			mSprite[i][n].SetSize(TileSize, TileSize);
			// Pivotの設定。左上をスプライトの中心点をする
			mSprite[i][n].SetPivot(Pivot::TopLeft);
		}
	}
}

// 終了
void Tilemap::Term()
{
	// マップデータを解放
	_clearMapData();
	// テクスチャの解放
	for (int i = 0; i < RENDER_ROW_NUM; i++)
	{
		for (int n = 0; n < RENDER_COL_NUM; n++)
		{
			mSprite[i][n].Term();
		}
	}

	// テクスチャの廃棄
	mTexture.Unload();
}

// 更新
void Tilemap::Update()
{
	// マップデータが生成されていなければ何もしないで関数を抜ける
	if (mpMapData == nullptr)
	{
		return;
	}
	// 現在のカメラ位置
	Vector2f cameraPosition = RenderManager_I->GetCamera().GetPosition();

	// カメラ位置をもとに画面の左上に位置するタイルの列・行を求める
	float Left = cameraPosition.x - WINDOW_WIDTH / 2.0f; // 画面左端の座標
	float Top = cameraPosition.y + WINDOW_HEIGHT / 2.0f; // 画面上端の座標
	int LeftCol = (int)(Left / TileSize); // 画面左端のタイルの列
	int TopRow = (int)(-Top / TileSize); // 画面上端のタイルの行

	// タイル描画用のスプライトに、位置とUV座標を設定する
	for (int i = 0; i < RENDER_ROW_NUM; i++)
	{
		for (int n = 0; n < RENDER_COL_NUM; n++)
		{
			// mSprite[i][n]が表示するタイルの列・行
			int col = LeftCol + n;
			int row = TopRow + i;

			// マップデータの領域外を参照しないようにチェック
			if (col >= mColNum || row >= mRowNum)
			{
				// 無駄な描画命令を出さないように非表示にしておく
				mSprite[i][n].SetVisible(false);
				continue;
			}

			// 位置を設定
			mSprite[i][n].SetPosition((float)col * TileSize, (float)-row * TileSize);

			// マップデータからタイルIDを取得
			int id = mpMapData[row][col];

			// スプライトのUV座標設定
			float w = 16.0f / 256.0f;
			float h = 16.0f / 256.0f;
			float u = (float)(id % 16) * w;
			float v = (float)(id / 16) * h;
			mSprite[i][n].SetTexCoord(u, v, w, h);

			if (id == 0)
			{
				mSprite[i][n].SetVisible(false);
			}
			else
			{
				mSprite[i][n].SetVisible(true); // 表示設定をしておく
			}
		}
	}
}

// 描画
void Tilemap::Render()
{
	// スプライトの描画
	for (int i = 0; i < RENDER_ROW_NUM; i++)
	{
		for (int n = 0; n < RENDER_COL_NUM; n++)
		{
			mSprite[i][n].Draw();
		}
	}
}

float Tilemap::GetTileSize()
{
	return TileSize;
}

// 指定した矩形の内側に壁が入り込んでいるかを返す
bool Tilemap::IsInsideWallRect(Vector2f _position, float _width, float _height) const
{
	// 矩形範囲内のすべてのタイルについて、壁であるか、矩形範囲に入り込んでいるかを判定する
	// まず矩形の四隅の座標を作る（中心点±幅の半分、中心点±高さの半分）
	float left = _position.x - _width / 2.0f;
	float right = _position.x + _width / 2.0f;
	float top = _position.y + _height / 2.0f;
	float bottom = _position.y - _height / 2.0f;

	// 矩形の四隅の座標をそれぞれマップデータの列・行に変換
	// これをもとに左上→右下までのタイルを１つずつ衝突判定していく
	int col_left = (int)(left / TileSize);
	int row_top = (int)(top / -TileSize);
	int col_right = (int)(right / TileSize);
	int row_bottom = (int)(bottom / -TileSize);

	for (int row = row_top; row <= row_bottom; row++)
	{
		for (int col = col_left; col <= col_right; col++)
		{
			// 壁でなければ次のタイルの判定を処理する
			if (!IsWall(col, row))
			{
				continue;
			}
			// 列と行から、壁と判定したタイルの中心座標を作る
			// 列xタイルサイズ、行xタイルサイズでタイルの左上の座標となり、
			// そこにタイルサイズの半分を+X方向、-Y方向に足すことでタイルの中心座標(x,y)となる
			float tile_x = (float)col * TileSize + (TileSize * 0.5f);
			float tile_y = (float)row * -TileSize - (TileSize * 0.5f);

			// 壁の中心点の座標と引数で指定された矩形の中心点の座標との差の大きさを得る
			float dx = fabsf(tile_x - _position.x);
			float dy = fabsf(tile_y - _position.y);

			// 二つの矩形が入り込んでいるかをチェックする
			if (dx <= (_width + TileSize) * 0.5f && dy <= (_height + TileSize) * 0.5f)
			{
				return true;
			}
		}
	}
	return false;
}

bool Tilemap::IsInsideWallCircle(Vector2f _position, float _radius) const
{
#ifdef max
#undef max
#endif
	float left = _position.x - _radius;
	float right = _position.x + _radius;
	float top = _position.y + _radius;
	float bottom = _position.y - _radius;

	int col_left = (int)(left / TileSize);
	int col_right = (int)(right / TileSize);
	int row_top = (int)(top / -TileSize);
	int row_bottom = (int)(bottom / -TileSize);

	for (int row = row_top; row <= row_bottom; row++)
	{
		for (int col = col_left; col <= col_right; col++)
		{
			if (!IsWall(col, row))
				continue;

			float tile_x = col * TileSize + TileSize * 0.5f;
			float tile_y = row * -TileSize - TileSize * 0.5f;

			float dx = std::max(std::abs(_position.x - tile_x) - TileSize * 0.5f, 0.0f);
			float dy = std::max(std::abs(_position.y - tile_y) - TileSize * 0.5f, 0.0f);

			if ((dx * dx + dy * dy) <= _radius * _radius)
			{
				return true;
			}
		}
	}
	return false;
}

// マップをCSVDataから生成する
void Tilemap::CreateMap(int colNum, int rowNum, CSVData* pMapdata)
{
	if (pMapdata == nullptr)
		return;

	// 現在のマップデータをリセットする
	_clearMapData();

	// 列数・行数を記録
	mColNum = colNum;
	mRowNum = rowNum;

	// 列数*行数分の配列を確保する
	mpMapData = new int* [mRowNum];
	for (int i = 0; i < mRowNum; i++)
	{
		mpMapData[i] = new int[mColNum];
	}
	// 行数分繰り返し
	for (int i = 0; i < mRowNum; i++)
	{
		// 列数分繰り返し
		for (int n = 0; n < mColNum; n++)
		{
			// n列i行目のタイルIDをCSVDataから取得
			int id = pMapdata->GetInt(n + (i * COL_NUM));
			// マップデータのn列i行目のタイルIDを上書き
			mpMapData[i][n] = id;
		}
	}
}

Vector2f Tilemap::GetMapSize() const
{
	Vector2f result(
		mColNum * TileSize,
		mRowNum * TileSize
	);
	return result;
}

// 指定された列・行が壁であるか否かを戻す
bool Tilemap::IsWall(int _col, int _row) const
{
	// 不正値チェック
	if (_col < 0 || _col >= mColNum || _row < 0 || _row >= mRowNum)
	{
		return false;
	}

	// 指定の列・行のタイルIDを取得する
	int id = mpMapData[_row][_col];

	// タイルID1番を壁と判定する
	if (id == 1)
	{
		return true;
	}
	return false;
}

void Tilemap::_clearMapData()
{
	// マップデータが確保されていることを確認して
	if (mpMapData != nullptr)
	{
		// 先にmpMapData[0]~mpMapData[mRowNum-1]までの配列を解放する
		for (int i = 0; i < mRowNum; i++)
		{
			SAFE_DELETE_ARRAY(mpMapData[i]);
		}
		// 最後にint*配列であるmpMapDataを解放する
		SAFE_DELETE_ARRAY(mpMapData);
		// マップデータを消したので、マップの列数・行数もリセットしておく
		mRowNum = 0;
		mColNum = 0;
	}
}
