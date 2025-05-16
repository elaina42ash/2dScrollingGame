#pragma once
#include <vector>

#include "InputEvent.h"

namespace GameInput
{
	// 输入缓冲器：跨帧维护输入队列与超时控制
	class InputBuffer {
	private:
		std::vector<GameInput::InputEvent> buffer_;
		float lastInputTime_ = -1.0f;
		float activeWindow_ = 0.0f;
		bool accepting_ = false;

	public:
		void Push(GameInput::LogicalInput _input, float _eventTime, float _inputWindowDuration);

		void Update(float _currentTime);

		const std::vector<GameInput::InputEvent>& GetBuffer() const;

		bool IsAcceptingInput() const;
	};

	inline void InputBuffer::Push(GameInput::LogicalInput _input, float _eventTime, float _inputWindowDuration)
	{
		if (!accepting_ || (_eventTime - lastInputTime_) > activeWindow_) {
			buffer_.clear();
			accepting_ = true;
		}
		buffer_.push_back({ _input, _eventTime });
		lastInputTime_ = _eventTime;
		activeWindow_ = _inputWindowDuration;
	}

	inline void InputBuffer::Update(float _currentTime)
	{
		if (accepting_ && (_currentTime - lastInputTime_) > activeWindow_) {
			buffer_.clear();
			accepting_ = false;
		}
	}

	inline const std::vector<GameInput::InputEvent>& InputBuffer::GetBuffer() const
	{
		return buffer_;
	}

	inline bool InputBuffer::IsAcceptingInput() const
	{
		return accepting_;
	}
};