#pragma once
#include <map>
#include "Player/Player.h"
#include "SceneMng/SceneMng.h"
#include "UI/UIMng.h"

#define WORLD_I World::Instance()
class World
{
public:
	using PlayerID = size_t;
private:
	SceneMng sceneMng_;

	UIMng uiMng_;

	std::map<PlayerID, Player*> players_;

	PlayerID mainPlayerID_ = 0;

	std::vector<PlayerID> controlledPlayerIDs_;

	std::vector<IGameObject*> globalObjects_;
public:
	static World& Instance();
	World() = default;
	World(const World& _other) = delete;
	World(World&& _other) noexcept = delete;
	World& operator=(const World& _other) = delete;
	World& operator=(World&& _other) noexcept = delete;

	void Init();
	void Update();
	void Render();
	void Term();

	void RegisterPlayer(PlayerID _id, Player* player);

	void UnRegisterPlayer(PlayerID _id);

	void DestroyPlayer(PlayerID _id);

	Player* AccessPlayer(PlayerID _id);

	Player* AccessMainPlayer();

	std::map<PlayerID, Player*>& AccessAllPlayers();

	const std::vector<PlayerID>& GetControlledPlayerIDs() const;

	void SetControlledPlayerIDs(const std::vector<PlayerID>& _ids);

	void DestroyAllPlayers();

	void SetMainPlayerID(PlayerID _id);

	PlayerID GetMainPlayerID() const;

	void RegisterGlobalObject(IGameObject* _obj);

	void UnRegisterGlobalObject(IGameObject* _obj);

	std::vector<IGameObject*>& AccessGlobalObjects();

	Scene* AccessCurrentScene();

	UIMng* AccessUIMng();

	void InitGlobalUI();

	void LoadSceneUI(SceneType _type);

	void UnloadSceneUI();
};
