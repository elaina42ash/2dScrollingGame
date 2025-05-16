#pragma once

enum class SwordMode
{
	NONE= -1,

	FIRST = 0,
	EQUIPPED = FIRST,
	ATTACKING,
	DROPPED,

	COUNT
};