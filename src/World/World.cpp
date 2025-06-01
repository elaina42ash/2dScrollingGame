#include "World/World.h"
#include "AppDef.h"
#include "Fwk/Framework.h"
#include "GamePlayData/GamePlayData.h"
#include "Mst/StageDataMst.h"
#include "Scene/Scene.h"
/**
 * @brief 获取 World 单例实例。
 */
World& World::Instance()
{
    static World instance;
    return instance;
}

/**
 * @brief 初始化游戏世界，包括渲染系统、数据资源、玩家和初始场景。
 */
void World::Init()
{
    // 渲染系统初始化（主摄像机与 UI 摄像机）
    RenderManager_I->AddLayer("UI");
    {
        Camera camera;
        camera.SetPosition(WINDOW_WIDTH / 2.0f, -WINDOW_HEIGHT / 2.0f);
        RenderManager_I->SetCamera(camera);
    }
    {
        Camera camera;
        camera.SetName("UI");
        camera.AddRenderLayer("UI");
        camera.SetActive(true);
        camera.SetPosition(WINDOW_WIDTH / 2.0f, -WINDOW_HEIGHT / 2.0f);
        RenderManager_I->SetCamera(camera);
    }

    // 游戏数据初始化
    GetGamePlayData().Init();
    GetStageDataMst().Init();

    // 初始化第一个场景（例如 Title）

    sceneMng_.Init(SceneType::Title);

}

/**
 * @brief 每帧更新逻辑，包括场景更新、受控玩家更新、全局对象更新。
 */
void World::Update()
{
    sceneMng_.Update();

    // 更新全局对象（例如 UI、常驻对象）
    for (auto* obj : globalObjects_)
    {
        if (obj && obj->IsActive())
            obj->Update();
    }


}

/**
 * @brief 每帧渲染调用，顺序为场景 → 玩家 → 全局对象。
 */
void World::Render()
{
    sceneMng_.Render();

    // 渲染全局对象(UI 等)
    for (auto* obj:globalObjects_)
    {
        if (obj && obj->IsActive())
            obj->Render();
    }

}

/**
 * @brief 游戏退出或切换时的清理逻辑，释放玩家与场景资源。
 */
void World::Term()
{
    DestroyAllPlayers();    // 删除玩家
    globalObjects_.clear(); // 清除全局对象引用
    sceneMng_.Term();       // 场景资源释放
 
}

/**
 * @brief 注册玩家至 players_ 映射表。
 */
void World::RegisterPlayer(PlayerID _id, Player* player)
{
    players_[_id] = player;
}

/**
 * @brief 从玩家映射中移除指定玩家（不销毁）。
 */
void World::UnRegisterPlayer(PlayerID _id)
{
    players_.erase(_id);
}

/**
 * @brief 销毁指定玩家对象并释放内存。
 */
void World::DestroyPlayer(PlayerID _id)
{
    auto it = players_.find(_id);
    if (it == players_.end())
        return;
    if (it->second)
    {
        it->second->Term();
        delete it->second;
        it->second = nullptr;
    }
}

/**
 * @brief 获取指定 ID 的玩家指针。
 */
Player* World::AccessPlayer(PlayerID _id)
{
    auto it = players_.find(_id);
    return it != players_.end() ? it->second : nullptr;
}

/**
 * @brief 获取主控玩家对象（封装 AccessPlayer）。
 */
Player* World::AccessMainPlayer()
{
    return AccessPlayer(mainPlayerID_);
}

/**
 * @brief 获取所有玩家引用。
 */
std::map<World::PlayerID, Player*>& World::AccessAllPlayers()
{
    return players_;
}

/**
 * @brief 获取当前控制的玩家 ID 列表。
 */
const std::vector<World::PlayerID>& World::GetControlledPlayerIDs() const
{
    return controlledPlayerIDs_;
}

/**
 * @brief 设置当前控制的玩家 ID 列表。
 */
void World::SetControlledPlayerIDs(const std::vector<PlayerID>& _ids)
{
    controlledPlayerIDs_ = _ids;
}

/**
 * @brief 删除并释放所有玩家对象。
 */
void World::DestroyAllPlayers()
{
    for (auto& pair : players_)
    {
        if (pair.second)
        {
            pair.second->Term();
            delete pair.second;
            pair.second = nullptr;
        }
    }
    players_.clear();
}

/**
 * @brief 设置主控玩家 ID。
 */
void World::SetMainPlayerID(PlayerID _id)
{
    mainPlayerID_ = _id;
}

/**
 * @brief 获取主控玩家 ID。
 */
World::PlayerID World::GetMainPlayerID() const
{
    return mainPlayerID_;
}

/**
 * @brief 注册全局对象用于跨场景使用。
 */
void World::RegisterGlobalObject(IGameObject* _obj)
{
    if (_obj && std::find(globalObjects_.begin(), globalObjects_.end(), _obj) == globalObjects_.end())
        globalObjects_.push_back(_obj);
}

/**
 * @brief 注销全局对象。
 */
void World::UnRegisterGlobalObject(IGameObject* _obj)
{
    auto it = std::find(globalObjects_.begin(), globalObjects_.end(), _obj);
    if (it != globalObjects_.end())
        globalObjects_.erase(it);
}

/**
 * @brief 获取当前所有全局对象引用。
 */
std::vector<IGameObject*>& World::AccessGlobalObjects()
{
    return globalObjects_;
}

/**
 * @brief 获取当前活动场景对象。
 */
Scene* World::AccessCurrentScene()
{
    return sceneMng_.AccessCurrentScene();
}

