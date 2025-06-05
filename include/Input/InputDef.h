#pragma once

namespace GameInput
{
	enum class Axis
	{
		NONE = -1,

		FIRST = 0,
		VERTICAL = FIRST,
		HORIZONTAL,

		COUNT
	};

	enum class GamepadNumber
	{
		NONE = -1,

		FIRST = 0,
		GAMEPAD_NUMBER_1 = FIRST,
		GAMEPAD_NUMBER_2,

		COUNT
	};

	enum class GamepadStick {
		NONE = -1,

		FIRST = 0,
		LEFT = FIRST,
		RIGHT,

		Count,
	};

	enum class PhysicalInput
	{
		NONE = -1,

		FIRST = 0,
		KEY_W = FIRST,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_E,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_G,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_SPACE,
		KEY_SHIFT,
		LEFT_MOUSE,

		GAMEPAD_BUTTON_B,
		GAMEPAD_BUTTON_A,
		GAMEPAD_BUTTON_X,
		GAMEPAD_BUTTON_Y,

		COUNT
	};

	enum class LogicalInput
	{
		NONE = -1,

		FIRST = 0,
		MOVE_UP = FIRST,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		SWITCH_WEAPON,
		JUMP,
		ATTACK,
		DASH,
		INTERACT,
		DROP_WEAPON,

		COUNT
	};

};

