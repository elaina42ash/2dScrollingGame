#pragma once
#include <map>
#include <vector>
#include "Enemy/EnemyMng.h"
#include "GameObject/IDetachableObject.h"
#include "GameObject/IGameObject.h"
#include "GameObject/IStaticObject.h"
#include "Mst/StageData.h"
#include "Player/Player.h"
#include "Tilemap/Tilemap.h"

class GameObjectMng
{
	using PlayerID = size_t;
private:
	std::vector<IGameObject*> allObjects_;

	std::vector<IGameObject*> detachableObjects_;
	std::vector<IGameObject*> activeDetachableObjects_;

	std::vector<IGameObject*> mapBoundObjects_;
	std::vector<IGameObject*> activeMapBoundObjects_;

	std::map<PlayerID, Player*> players_;

	EnemyMng enemyMng_;
	Tilemap* tilemap_;

public:
	GameObjectMng() = default;

	void Init(StageData* stageData_);

	void Update();

	void Render();

	void Term();

private:

	void RegisterDetachable(IGameObject* _obj);

	void RegisterStatic(IGameObject* _obj);

	inline void UnregisterDetachable(IGameObject* _obj);

	inline void UnregisterStatic(IGameObject* _obj);

	template <typename T>
	T* CreateGameObject();

	void UnregisterPlayer(Player* _obj);

	void DestroyGameObject(IGameObject* _obj);

	void DestroyAllGameObjects();

	bool IsManagedObject(IGameObject* _obj) const;

	IGameObject* FindObjectByTag(const char* _tag) const;

	void RefreshActiveObjects();

	std::map<PlayerID, Player*>& AccessAllPlayers();

	Player* FindPlayer(PlayerID _id);

	template <typename T>
	void ForEachObjectOfType(std::function<void(T*)> Func);

	// 注册玩家
	void RegisterPlayer(PlayerID _id, Player* _player);



	// 激活/冻结对象
	void SetObjectActive(IGameObject* _obj, bool _active);

	// 地图切换清理
	void ClearMapBoundObjects();

	void MarkToDestroy(IGameObject* _obj);

	void DestroyMarkedObjects();

	bool IsHeldByCharacter(const IDetachableObject* _obj);
};

inline void GameObjectMng::RegisterDetachable(IGameObject* _obj)
{
	auto it = find(detachableObjects_.begin(), detachableObjects_.end(), _obj);

	if (it != detachableObjects_.end())
		return;

	detachableObjects_.push_back(_obj);

	if (_obj->GetActive())
	{
		auto itActive = find(activeDetachableObjects_.begin(), activeDetachableObjects_.end(), _obj);
		if (itActive == activeDetachableObjects_.end())
			activeDetachableObjects_.push_back(_obj);
	}
}


inline  void GameObjectMng::RegisterStatic(IGameObject* _obj)
{
	auto it = find(mapBoundObjects_.begin(), mapBoundObjects_.end(), _obj);
	if (it != mapBoundObjects_.end())
		return;

	mapBoundObjects_.push_back(_obj);

	if (_obj->GetActive())
	{
		auto itActive = find(activeMapBoundObjects_.begin(), activeMapBoundObjects_.end(), _obj);
		if (itActive == activeMapBoundObjects_.end())
			activeMapBoundObjects_.push_back(_obj);
	}
}

inline void GameObjectMng::UnregisterDetachable(IGameObject* _obj)
{
	auto it = find(detachableObjects_.begin(), detachableObjects_.end(), _obj);
	if (it != detachableObjects_.end())
		detachableObjects_.erase(it);

	auto itActive = find(activeDetachableObjects_.begin(), activeDetachableObjects_.end(), _obj);
	if (itActive != activeDetachableObjects_.end())
		activeDetachableObjects_.erase(it);
}

inline void GameObjectMng::UnregisterStatic(IGameObject* _obj)
{
	auto it = find(mapBoundObjects_.begin(), mapBoundObjects_.end(), _obj);
	if (it != mapBoundObjects_.end())
		mapBoundObjects_.erase(it);

	auto itActive = find(activeMapBoundObjects_.begin(), activeMapBoundObjects_.end(), _obj);
	if (itActive != activeMapBoundObjects_.end())
		activeMapBoundObjects_.erase(it);
}

template <typename T>
T* GameObjectMng::CreateGameObject()
{
	static_assert(std::is_base_of<IGameObject, T>::value, "T must derive from IGameObject");
	static_assert(!std::is_base_of<Player, T>::value, "CreateGameObject<T> cannot be used with Player or its subclasses. Use CreatePlayer() instead.");

	IGameObject* basePtr = new T();

	T* casted = dynamic_cast<T*>(basePtr);
	if (!casted)
	{
		delete basePtr;
		throw std::runtime_error("CreateGameObject: Failed to cast to target type T.");
	}

	allObjects_.push_back(basePtr);

	if (auto* detachableObject = dynamic_cast<IDetachableObject*>(basePtr))
	{
		RegisterDetachable(basePtr);
	}

	if (auto* staticObject = dynamic_cast<IStaticObject*>(basePtr))
	{
		RegisterStatic(basePtr);
	}

	return casted;
}

template <typename T>
void GameObjectMng::ForEachObjectOfType(function<void(T*)> Func)
{
	for (auto* obj : allObjects_)
	{
		if (!obj)
			continue;

		T* casted = dynamic_cast<T*>(obj);
		if (casted)
			Func(casted);
	}
}

