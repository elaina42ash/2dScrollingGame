#pragma once
#include "InputDef.h"
#include "Lib/Math/TVector2.h"

namespace GameInput
{
	class ILogicalInputAdapter
	{
	public:
		virtual ~ILogicalInputAdapter() = default;

		virtual bool GetKey(GameInput::LogicalInput _input) const = 0;

		virtual bool GetKeyDown(LogicalInput _input) const = 0;

		virtual bool GetKeyUp(LogicalInput _input) const = 0;

		virtual bool GetButton(GamepadNumber _padNo, LogicalInput _input) const = 0;

		virtual bool GetButtonDown(GamepadNumber _padNo, LogicalInput _input) const = 0;

		virtual bool GetButtonUp(GamepadNumber _padNo, LogicalInput _input) const = 0;

		virtual  void GetStickInput(GamepadNumber _padNo, GamepadStick _stick, Lib::Math::Vector2f* pOut) const = 0;

		virtual float GetAxis(Axis _axis) const = 0;

		virtual float GetAxisRaw(Axis _axis) const =0;
	};
}

