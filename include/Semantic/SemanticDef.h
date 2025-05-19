#pragma once
namespace GameSemantic
{
	enum class Semantic
	{
		NONE = -1,

		FIRST = 0,
		START_MOVE = FIRST,
		STOP_MOVE,
		START_JUMP,
		RELEASE_JUMP,
		START_ATTACK,
		START_DASH,
		START_SWITCH_WEAPON,


		COUNT
	};
}
