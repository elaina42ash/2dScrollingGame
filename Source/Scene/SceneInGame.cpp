#include "SceneInGame.h" // SceneInGameクラスのヘッダーファイルをインクルード
#include "AppDef.h" // アプリケーション定義用のヘッダーファイル
#include "Fwk/Framework.h" // フレームワーク関連のヘッダーファイル
#include "Fwk/File/CSVFile.h" // CSVファイル操作用のヘッダーファイル
#include "Fwk/File/KeyValueFile.h" // キーバリューファイル操作用のヘッダーファイル
#include "GamePlayData/GamePlayData.h" // ゲームプレイデータ管理用のヘッダーファイル
#include "Mst/StageDataMst.h" // ステージデータ管理用のヘッダーファイル
#include "World/World.h" // ワールド管理用のヘッダーファイル
// 初期化
void SceneInGame::Init()
{
    Scene::Init(); // 基底クラスの初期化処理を呼び出し

    // 現在のステージ番号を取得
    int stageNo = GetGamePlayData().GetStageNo();
    // ステージデータを取得
    StageData* pStageData = GetStageDataMst().Get(0);
    KeyValueFile mapdataFile;
    // ステージデータが存在する場合、マップデータをロード
    if (pStageData)
        mapdataFile.Load(pStageData->mapFile_);

    // マップの列数と行数を取得
    int col = mapdataFile.GetInt("Col");
    int row = mapdataFile.GetInt("Row");
    // レンダーマップを作成
    tilemap_.CreateRenderMap(WINDOW_WIDTH / tilemap_.GetTileSize() + 2, WINDOW_HEIGHT / tilemap_.GetTileSize() + 2);
    // タイルマップを初期化
    tilemap_.Init();
    // マップデータを作成
    tilemap_.CreateMap(col, row, mapdataFile.GetCSVData("Data"));

    // プレイヤーオブジェクトを作成
    Player* player = new Player;
    // メインプレイヤーのIDを設定
    WORLD_I.SetMainPlayerID(0);
    // コントロールするプレイヤーIDを設定
    WORLD_I.SetControlledPlayerIDs({ 0 });
    // プレイヤーを登録
    WORLD_I.RegisterPlayer(0, player);
    // プレイヤーを初期化
    player->Init();
    // シーンコンテキストをバインド
    player->BindSceneContext(this);
    // ゲームプレイAPIをバインド
    player->BindSceneGameplayAPI(this);
    // プレイヤーを有効化
    player->Enable();
    // スタート位置データを取得
    CSVData* pStartPos = mapdataFile.GetCSVData("Start");
    if (pStartPos != nullptr)
    {
        // スタート位置のX座標とY座標を取得
        float x = pStartPos->GetFloat(0);
        float y = pStartPos->GetFloat(1);
        // 初期位置を設定
        Vector2f initialPosition = { x, y };
        // 初期位置を設定するプレイヤーを指定
        Player* playerToInitPosition = player;
        if (playerToInitPosition)
        {
            // トランスフォームコンポーネントを取得
            auto* transform = playerToInitPosition->GetComponent<ITransformComponent>();
            // プレイヤーを初期位置に移動
            if (transform)
                transform->MoveTo(initialPosition);
        }
    }

    {
        // 静的オブジェクト管理を初期化
        staticObjectMng_.Init();
        // 静的オブジェクトのプールを生成
        staticObjectMng_.GeneratePool("IronSpike", 100);
        CSVFile csvFile;
        // ステージデータが存在する場合、静的オブジェクト配置ファイルをロード
        if (pStageData)
            csvFile.Load(pStageData->staticObjectArrangementFile_);
        // CSVデータを出力
        csvFile.PrintCSVData();
        // 静的オブジェクトを作成
        staticObjectMng_.CreateStaticObjects(csvFile.GetCSVData(), tilemap_.GetTileSize());
    }

    // 敵管理を初期化
    {
        enemyMng_.Init();
        // 各敵のプールを生成
        enemyMng_.GeneratePool("Slime", 30);
        enemyMng_.GeneratePool("Ghost", 30);
        enemyMng_.GeneratePool("Skull", 30);
        enemyMng_.GeneratePool("Onibi", 30);
        CSVFile csvFile;
        // ステージデータが存在する場合、敵配置ファイルをロード
        if (pStageData)
            csvFile.Load(pStageData->enemyArrangementFile_);
        // CSVデータを出力
        csvFile.PrintCSVData();
        // 敵を作成
        enemyMng_.CreateEnemies(csvFile.GetCSVData(), tilemap_.GetTileSize(), this, this);
    }

    // BGMファイルの読み込み
    mSound.Load(BGM_URL);
    // 音源の初期化
    mSoundSource.Init(mSound);
    // BGMを繰り返し再生
    mSoundSource.Play(-1);

    // シーンUIをロード
    WORLD_I.LoadSceneUI(SceneType::InGame);

    // 次のシーンの初期値を設定
    mNextScene = SceneType::None;
}
// 終了処理
void SceneInGame::Term()
{
    Scene::Term();
    // 静的オブジェクト管理の終了処理
    staticObjectMng_.Term();
    // 敵管理の終了処理
    enemyMng_.Term();
    // タイルマップの終了処理
    tilemap_.Term();
    // BGMを停止
    mSoundSource.Stop();
    // 音源を解放
    mSoundSource.Term();
    // 読み込んだ音声ファイルを破棄
    mSound.Unload();
    // シーンUIをアンロード
    WORLD_I.UnloadSceneUI();
}
// 更新処理
void SceneInGame::Update()
{
    Scene::Update();

    // プレイヤーを取得
    Player* player = WORLD_I.AccessMainPlayer();
    if (player && player->IsActive())
    {
        // プレイヤーの更新処理
        player->Update();
        // プレイヤーの現在位置にカメラの位置を合わせる
        Vector2f cameraPosition = player->GetPosition();
        // マップ全体のサイズを取得
        Vector2f mapSize = tilemap_.GetMapSize();
        // カメラの移動可能範囲を設定
        float cameraArea_left = WINDOW_WIDTH / 2.0f;
        float cameraArea_top = -WINDOW_HEIGHT / 2.0f;
        float cameraArea_right = mapSize.x - WINDOW_WIDTH / 2.0f;
        float cameraArea_bottom = -mapSize.y + WINDOW_HEIGHT / 2.0f;
        // カメラ位置を調整
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
        // ステージクリア状態を確認
        if (player->IsStageCleared())
        {
            needReload_ = true;
        }
        // プレイヤーが死亡した場合、次のシーンをゲームオーバーに設定
        if (player->IsDead())
        {
            mNextScene = SceneType::GameOver;
        }
    }

    // 敵管理の更新処理
    enemyMng_.Update();
    // 静的オブジェクト管理の更新処理
    staticObjectMng_.Update();
    // タイルマップの更新処理
    tilemap_.Update();
}
// 描画処理
void SceneInGame::Render()
{
    Scene::Render();
    // タイルマップの描画
    tilemap_.Render();
    // プレイヤーを取得
    Player* player = WORLD_I.AccessMainPlayer();
    if (player)
    {
        // プレイヤーの描画
        player->Render();
    }
    // 敵管理の描画
    enemyMng_.Render();
    // 静的オブジェクト管理の描画
    staticObjectMng_.Render();
}
float SceneInGame::GetTileSize()
{
    return tilemap_.GetTileSize();
}
bool SceneInGame::IsInsideWallRect(Lib::Math::Vector2f _position, float _width, float _height) const
{
    return tilemap_.IsInsideWallRect(_position, _width, _height);
}
bool SceneInGame::IsInsideWallCircle(Lib::Math::Vector2f _position, float _radius) const
{
    return tilemap_.IsInsideWallCircle(_position, _radius);
}
void SceneInGame::CreateEnemy(const char* _enemyName, Lib::Math::Vector2f _position)
{
    enemyMng_.CreateEnemy(_enemyName, _position, this, this);
}
