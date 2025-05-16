#pragma once
#include "InputDef.h"

namespace GameInput
{
	class IInputMapper
	{
	public:
		virtual  ~IInputMapper() = default;

		virtual void BindPhysicalToLogical(GameInput::PhysicalInput _physicalInput, GameInput::LogicalInput _logicalInput) = 0;

		virtual GameInput::LogicalInput GetMappedLogicalInput(GameInput::PhysicalInput _physicalInput) const = 0;

		virtual GameInput::PhysicalInput GetMappedPhysicalInput(GameInput::LogicalInput _logicalInput) const = 0;

	};
}
