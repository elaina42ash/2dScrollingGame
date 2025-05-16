#pragma once
enum class WeaponMode
{
	NONE = -1,

	FIRST = 0,
	EQUIPPED = FIRST,
	ATTACKING,
	DROPPED,

	COUNT
};