#pragma once
#include "Player/Player.h"
#include "Scene/SceneMng.h"

class World
{
public:
	using PlayerID = size_t;

private:
	SceneMng sceneMng_;

private:
	Player* CreatePlayerObject(PlayerID _id);
};
