#pragma once
#include <vector>

#include "ComboStep.h"
#include "InputEvent.h"

namespace GameInput
{
	// 一个组合输入定义
	struct ComboInput {
		std::vector<ComboStep> sequence;

		bool Match(const std::vector<InputEvent>& _history, float _currentTime) const;
	};

	inline bool ComboInput::Match(const std::vector<InputEvent>& _history, float _currentTime) const
	{
		if (_history.size() < sequence.size()) return false;

		int historyIndex = static_cast<int>(_history.size()) - 1;
		float timrAnchor = _currentTime;

		for (int i = static_cast<int>(sequence.size()) - 1; i >= 0; i--, historyIndex--) {
			if (historyIndex < 0) return false;
			const auto& step = sequence[i];
			const auto& inputEvent = _history[historyIndex];
			if (inputEvent.input != step.input) return false;
			if ((timrAnchor - inputEvent.timestamp) > step.maxTimeSinceLast) return false;
			timrAnchor = inputEvent.timestamp;
		}
		return true;
	}
}
