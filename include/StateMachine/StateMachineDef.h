#pragma once

namespace StateMachine_C
{
	enum class Comparator
	{
		NONE = -1,

		FIRST = 0,
		EQUAL = FIRST,
		GREATER,
		LESS,
		NOT_EQUAL,

		COUNT
	};

	enum class ParameterType
	{
		NONE,

		FIRST,
		BOOL = FIRST,
		INT,
		FLOAT,

		COUNT
	};
}
