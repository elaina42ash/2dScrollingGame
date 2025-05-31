#pragma once

enum class PlayerAnimationType
{
	NONE = -1,

	FIRST = 0,

	IDLE = FIRST,
	RUN,
	ATTACK_SWORD,
	ATTACK_KATANA,
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