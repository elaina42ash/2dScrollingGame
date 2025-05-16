#pragma once
#include "InputDef.h"

namespace GameInput
{
	// 单次输入事件（记录时间）
	struct InputEvent {
		LogicalInput input;
		float timestamp;
	};
}
