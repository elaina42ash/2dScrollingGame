#pragma once
#include "InputDef.h"

namespace GameInput
{
	// 组合输入步骤
	struct ComboStep {
		LogicalInput input;
		float maxTimeSinceLast; // 从上一步到这一步允许的最大时间
	};
}
