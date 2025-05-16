#pragma once
#include <unordered_map>

#include "IInputMapper.h"
#include "InputDef.h"

namespace GameInput
{
	class InputMapper :public IInputMapper
	{
	public:
		InputMapper() = default;

	private:

		std::unordered_map<GameInput::PhysicalInput, GameInput::LogicalInput> physicalToLogical_;

		std::unordered_map<GameInput::LogicalInput, GameInput::PhysicalInput> logicalToPhysical_;

	public:

		void BindPhysicalToLogical(GameInput::PhysicalInput _physicalInput, GameInput::LogicalInput _logicalInput) override;

		GameInput::LogicalInput GetMappedLogicalInput(GameInput::PhysicalInput _physicalInput) const override;

		GameInput::PhysicalInput GetMappedPhysicalInput(GameInput::LogicalInput _logicalInput) const override;


	};

	inline void InputMapper::BindPhysicalToLogical(GameInput::PhysicalInput _physicalInput,
		GameInput::LogicalInput _logicalInput)
	{
		physicalToLogical_[_physicalInput] = _logicalInput;
		logicalToPhysical_[_logicalInput] = _physicalInput;
	}

	inline GameInput::LogicalInput InputMapper::GetMappedLogicalInput(GameInput::PhysicalInput _physicalInput) const
	{
		auto it = physicalToLogical_.find(_physicalInput);
		return it != physicalToLogical_.end() ? it->second : GameInput::LogicalInput::NONE;
	}

	inline GameInput::PhysicalInput InputMapper::GetMappedPhysicalInput(GameInput::LogicalInput _logicalInput) const
	{
		auto it = logicalToPhysical_.find(_logicalInput);
		return it != logicalToPhysical_.end() ? it->second : GameInput::PhysicalInput::NONE;
	}

}
