#pragma once

enum class PlayerAnimationType
{
	NONE = -1,

	FIRST = 0,

	IDLE_FRONT = FIRST,
	IDLE_RIGHT,
	IDLE_BACK,
	IDLE_LEFT,
	WALK_FRONT,
	WALK_RIGHT,
	WALK_BACK,
	WALK_LEFT,
	DYING,

	COUNT
};


enum class SwordAnimationType
{
	NONE = -1,

	FIRST = 0,
	SWING_RIGHT = FIRST,
	SWING_LEFT ,

	COUNT
};