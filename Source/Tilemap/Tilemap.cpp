#include "Tilemap.h"
// RenderMangerを使うのでinclude
#include "Fwk/Framework.h"
// ウインドウサイズの定数を使うのでinclude
#include "AppDef.h"

// 初期化
void Tilemap::Init() {
	// マップサイズを初期化
	colNum_ = 0;
	rowNum_ = 0;
	// マップデータを収める二次元配列のポイントを初期化
	mapData_ = nullptr;

	// テクスチャファイルの読み込む
	texture_.Load(SOURCE_TILE_FILE_URL);

	// スプライトの初期化と各種設定
	for (int i = 0; i < render_row_num; i++)
	{
		for (int n = 0; n < render_col_num; n++)
		{
			// 初期化
			sprite_[i][n].Init();
			// テクスチャ設定
			sprite_[i][n].SetTexture(texture_);
			// サイズを設定
			sprite_[i][n].SetSize(TileSize, TileSize);
			// Pivotの設定。左上をスプライトの中心点をする
			sprite_[i][n].SetPivot(Pivot::TopLeft);
		}
	}
}

// 終了
void Tilemap::Term()
{
	// マップデータを解放
	ClearMapData();

	// テクスチャの解放
	for (int i = 0; i < render_row_num; i++)
	{
		for (int n = 0; n < render_col_num; n++)
		{
			sprite_[i][n].Term();
		}
	}

	if (sprite_ != nullptr) {
		for (int i = 0; i < render_row_num; ++i) {
			delete[] sprite_[i];
			sprite_[i] = nullptr;
		}
		delete[] sprite_;       
		sprite_ = nullptr;      
	}

	// テクスチャの廃棄
	texture_.Unload();
}

// 更新
void Tilemap::Update()
{
	// マップデータが生成されていなければ何もしないで関数を抜ける
	if (mapData_ == nullptr)
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
	for (int i = 0; i < render_row_num; i++)
	{
		for (int n = 0; n < render_col_num; n++)
		{
			// mSprite[i][n]が表示するタイルの列・行
			int col = LeftCol + n;
			int row = TopRow + i;

			// マップデータの領域外を参照しないようにチェック
			if (col >= colNum_ || row >= rowNum_)
			{
				// 無駄な描画命令を出さないように非表示にしておく
				sprite_[i][n].SetVisible(false);
				continue;
			}

			// 位置を設定
			sprite_[i][n].SetPosition((float)col * TileSize, (float)-row * TileSize);

			// マップデータからタイルIDを取得
			int id = mapData_[row][col];

			// スプライトのUV座標設定
			float w = SOURCE_TILE_SIZE / SOURCE_TILE_FILE_MAX_SIZE;
			float h = SOURCE_TILE_SIZE / SOURCE_TILE_FILE_MAX_SIZE;
			float u = (float)(id % (int)SOURCE_TILE_SIZE) * w;
			float v = (float)(id / (int)SOURCE_TILE_SIZE) * h;
			sprite_[i][n].SetTexCoord(u, v, w, h);


			if (id == 0)
			{
				sprite_[i][n].SetVisible(false);
			}
			else
			{
				sprite_[i][n].SetVisible(true); // 表示設定をしておく
			}
		}
	}
}

// 描画
void Tilemap::Render()
{
	// スプライトの描画
	for (int i = 0; i < render_row_num; i++)
	{
		for (int n = 0; n < render_col_num; n++)
		{
			sprite_[i][n].Draw();
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
			if (!IsBlockedTile(col, row))
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
			if (!IsBlockedTile(col, row))
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
	ClearMapData();

	// 列数・行数を記録
	colNum_ = colNum;
	rowNum_ = rowNum;

	// 列数*行数分の配列を確保する
	mapData_ = new int* [rowNum_];
	for (int i = 0; i < rowNum_; i++)
	{
		mapData_[i] = new int[colNum_];
	}
	// 行数分繰り返し
	for (int i = 0; i < rowNum_; i++)
	{
		// 列数分繰り返し
		for (int n = 0; n < colNum_; n++)
		{
			// n列i行目のタイルIDをCSVDataから取得
			int id = pMapdata->GetInt(n + (i * colNum_));
			// マップデータのn列i行目のタイルIDを上書き
			mapData_[i][n] = id;
		}
	}
}

Vector2f Tilemap::GetMapSize() const
{
	Vector2f result(
		colNum_ * TileSize,
		rowNum_ * TileSize
	);
	return result;
}

void Tilemap::CreateRenderMap(int _col, int _row)
{
	render_row_num = _row;
	render_col_num = _col;

	// 列数*行数分の配列を確保する
	sprite_ = new Sprite* [render_row_num];
	for (int i = 0; i < render_row_num; i++)
	{
		sprite_[i] = new Sprite[render_col_num];
	}

}

// 指定された列・行が壁であるか否かを戻す
bool Tilemap::IsBlockedTile(int _col, int _row) const
{
	// 不正値チェック
	if (_col < 0 || _col >= colNum_ || _row < 0 || _row >= rowNum_)
	{
		return false;
	}

	// 指定の列・行のタイルIDを取得する
	int id = mapData_[_row][_col];

	// タイルID1番を壁と判定する
	if ((id >= static_cast<int>(TileType::WALL_FIRST) && id<= static_cast<int>(TileType::WALL_END))|| (id >= static_cast<int>(TileType::PLATFORM_FIRST) && id <= static_cast<int>(TileType::PLATFORM_END)))
	{
		return true;
	}
	return false;
}

void Tilemap::ClearMapData()
{
	// マップデータが確保されていることを確認して
	if (mapData_ != nullptr)
	{
		// 先にmpMapData[0]~mpMapData[mRowNum-1]までの配列を解放する
		for (int i = 0; i < rowNum_; i++)
		{
			SAFE_DELETE_ARRAY(mapData_[i]);
		}
		// 最後にint*配列であるmpMapDataを解放する
		SAFE_DELETE_ARRAY(mapData_);
		// マップデータを消したので、マップの列数・行数もリセットしておく
		rowNum_ = 0;
		colNum_ = 0;
	}
}
