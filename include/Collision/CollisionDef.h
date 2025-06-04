#pragma once

// 衝突グループを示す定数
enum class CollisionGroup {
	NONE = -1,

	FIRST = 0,

	PLAYER = FIRST,
	WEAPON,
	ENEMY,
	IRON_SPIKE,
	DOOR,
	GOAL,
	DROPPED_ITEM,

	COUNT
};

enum class CollisionTag {
	NONE = -1,

	FIRST = 0,

	PLAYER = FIRST,
	SWORD,
	KATANA,

	COUNT
};