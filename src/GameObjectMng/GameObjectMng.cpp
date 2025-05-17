#include "GameObjectMng/GameObjectMng.h"
#include "AppDef.h"
#include "Fwk/Framework.h"
#include "Fwk/File/KeyValueFile.h"
#include "GameObject/DetachableObject.h"

void GameObjectMng::Init(StageData* stageData_)
{
	// 清空旧数据
	DestroyAllGameObjects();

	// 加载地图
	tilemap_ = new Tilemap;
	tilemap_->Init();
	KeyValueFile mapdataFile;
	if (stageData_)
		mapdataFile.Load(stageData_->MapFile);
	int col = mapdataFile.GetInt("Col");
	int row = mapdataFile.GetInt("Row");
	tilemap_->CreateMap(col, row, mapdataFile.GetCSVData("Data"));


	// 创建场景相关对象
	Player* player = CreatePlayerObject(0);
	player->SetTag("Player0");
	CSVData* pStartPos = mapdataFile.GetCSVData("Start");
	if (pStartPos != nullptr)
	{
		float x = pStartPos->GetFloat(0);
		float y = pStartPos->GetFloat(1);

		Vector2f initialPosition = { x,y };

		Player* playerToInitPosition = players_[0];

		if (playerToInitPosition)
		{
			auto* transform = playerToInitPosition->GetComponent<ITransformComponent>();
			if (transform)
				transform->MoveTo(initialPosition);
		}
	}

	// 初始化敌人管理器
	enemyMng_.Init();
	enemyMng_.GeneratePool("Slime", 10);
	enemyMng_.GeneratePool("Ghost", 10);
	enemyMng_.GeneratePool("Skull", 10);
	CSVFile csvFile;
	if (stageData_)
		csvFile.Load(stageData_->ArrangementFile);
	csvFile.PrintCSVData();
	enemyMng_.CreateEnemies(csvFile.GetCSVData());

	// 刷新激活状态列表
	RefreshActiveObjects();
}

void GameObjectMng::Update()
{
	// 刷新活跃对象状态（如必要）
	RefreshActiveObjects();

	// 所有对象更新
	for (auto* obj : activeDetachableObjects_)
	{
		if (obj)
			obj->Update();
	}

	for (auto* obj : activeMapBoundObjects_)
	{
		if (obj)
			obj->Update();
	}

	// 遍历所有玩家对象
	// 如果玩家对象存在且处于活跃状态，则调用其 Update 方法进行更新
	for (auto& pair : players_)
	{
		if (pair.second && pair.second->GetActive())
		{
			pair.second->Update();
			// プレイヤーの現在位置にカメラの位置を合わせる
			Vector2f cameraPosition = { 0.0f,0.0f };
			if (pair.second)
			{
				cameraPosition = pair.second->GetPosition();
			}

			// マップ全体のサイズを取得
			Vector2f mapSize = { 0.0f,0.0f };
			if (tilemap_)
				mapSize = tilemap_->GetMapSize();

			// カメラの移動可能範囲を作る
			float cameraArea_left = WINDOW_WIDTH / 2.0f; // 左端
			float cameraArea_top = -WINDOW_HEIGHT / 2.0f; // 右端
			float cameraArea_right = mapSize.x - WINDOW_WIDTH / 2.0f; // 上端
			float cameraArea_bottom = -mapSize.y + WINDOW_HEIGHT / 2.0f; // 下端

			// カメラ位置がカメラの移動範囲内に収めるように調整
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
			camera.SetName("camera_player");
			RenderManager_I->SetCamera(camera);
		}

	}

	enemyMng_.Update();

	DestroyMarkedObjects();
}

void GameObjectMng::Render()
{
	// 所有对象渲染
	for (auto* obj : activeDetachableObjects_)
	{
		if (obj)
			obj->Render();
	}

	for (auto* obj : activeMapBoundObjects_)
	{
		if (obj)
			obj->Render();
	}

	for (auto& pair : players_)
	{
		if (pair.second && pair.second->GetActive())
			pair.second->Render();
	}

	enemyMng_.Render();
}

void GameObjectMng::Term()
{
	DestroyAllGameObjects();

	enemyMng_.Term();

	if (tilemap_)
	{
		tilemap_->Term();     // 若有资源释放逻辑
		delete tilemap_;
		tilemap_ = nullptr;
	}
}

void GameObjectMng::UnregisterPlayer(Player* _obj)
{
	for (auto it = players_.begin(); it != players_.end(); )
	{
		if (it->second == _obj)
		{
			it = players_.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GameObjectMng::DestroyGameObject(IGameObject* _obj)
{
	if (!_obj)
		return;

	if (auto* detachableObject = dynamic_cast<DetachableObject*>(_obj))
		UnregisterDetachable(detachableObject);

	if (auto* staticObject = dynamic_cast<DetachableObject*>(_obj))
		UnregisterStatic(staticObject);

	if (Player* PlayerToUnregister = dynamic_cast<Player*>(_obj))
		UnregisterPlayer(PlayerToUnregister);

	auto it = find(allObjects_.begin(), allObjects_.end(), _obj);
	if (it != allObjects_.end())
	{
		if (*it != nullptr)
		{
			(*it)->Term();
			delete (*it);
			*it = nullptr;
		}
		allObjects_.erase(it);
	}
}

void GameObjectMng::DestroyAllGameObjects()
{
	for (auto it = allObjects_.begin(); it != allObjects_.end(); ++it)
	{
		if (*it)
		{
			(*it)->Term();
			delete (*it);
			(*it) = nullptr;
		}
	}

	allObjects_.clear();
	detachableObjects_.clear();
	activeDetachableObjects_.clear();
	mapBoundObjects_.clear();
	activeMapBoundObjects_.clear();
	players_.clear();
}

bool GameObjectMng::IsManagedObject(IGameObject* _obj) const
{
	if (!_obj)
		return false;

	return find(allObjects_.begin(), allObjects_.end(), _obj) != allObjects_.end();
}

IGameObject* GameObjectMng::FindObjectByTag(const char* _tag) const
{
	if (!_tag || *_tag == '\0')
		return nullptr;

	for (auto* obj : allObjects_)
	{
		if (!obj)
			continue;

		const char* tag = obj->GetTag();

		if (tag && strcmp(tag, _tag) == 0)
			return obj;
	}

	return nullptr;
}

void GameObjectMng::RefreshActiveObjects()
{
	activeDetachableObjects_.clear();
	for (auto* obj : detachableObjects_)
	{
		if (obj && obj->GetActive())
		{
			activeDetachableObjects_.push_back(obj);
		}
	}

	activeMapBoundObjects_.clear();
	for (auto* obj : mapBoundObjects_)
	{
		if (obj && obj->GetActive())
		{
			activeMapBoundObjects_.push_back(obj);
		}
	}
}

std::map<GameObjectMng::PlayerID, Player*>& GameObjectMng::AccessAllPlayers()
{
	return players_;
}

Player* GameObjectMng::FindPlayer(PlayerID _id)
{
	auto it = players_.find(_id);
	if (it == players_.end())
		return nullptr;
	return it->second;
}

void GameObjectMng::RegisterPlayer(PlayerID _id, Player* _player)
{
	if (!_player)
		return;

	if (players_.find(_id) != players_.end())
		return;

	players_[_id] = _player;
}



void GameObjectMng::SetObjectActive(IGameObject* _obj, bool _active)
{
	if (!_obj)
		return;

	if (_active)
		_obj->Enable();
	else
		_obj->Disable();

	if (auto* detachableObject = dynamic_cast<IDetachableObject*>(_obj))
	{
		auto& vec = activeDetachableObjects_;
		auto it = find(vec.begin(), vec.end(), _obj);

		if (_active)
		{
			if (it == vec.end())
			{
				vec.push_back(_obj);
			}
		}
		else
		{
			if (it != vec.end())
				vec.erase(it);
		}
	}
}

void GameObjectMng::ClearMapBoundObjects()
{
	for (auto* obj : mapBoundObjects_)
	{
		if (!obj)
			continue;

		DestroyGameObject(obj);
	}

	mapBoundObjects_.clear();
	activeMapBoundObjects_.clear();
}

void GameObjectMng::MarkToDestroy(IGameObject* _obj)
{
	if (_obj)
		_obj->MarkToDestroy();

}

void GameObjectMng::DestroyMarkedObjects()
{
	vector<IGameObject*> toDestroy;

	for (auto* obj : allObjects_)
	{
		if (obj && obj->IsMarkedToDestroy())
			toDestroy.push_back(obj);
	}

	for (auto* obj : toDestroy)
	{
		DestroyGameObject(obj);
	}
}

bool GameObjectMng::IsHeldByCharacter(const IDetachableObject* _obj)
{
	if (!_obj)
		return false;

	if (DetachableObjectState::HELD == _obj->GetState())
		return true;

	return false;
}
