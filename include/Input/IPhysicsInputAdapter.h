#pragma once
#include "InputDef.h"
#include "Lib/Math/TVector2.h"

namespace GameInput
{
	class IPhysicsInputAdapter
	{
	public:
		virtual ~IPhysicsInputAdapter() = default;

		virtual bool GetKey(PhysicalInput _input) const = 0;

		virtual bool GetKeyDown(PhysicalInput _input) const = 0;

		virtual bool GetKeyUp(PhysicalInput _input) const = 0;

		virtual bool GetButton(GamepadNumber _padNo, PhysicalInput _input) const = 0;

		virtual bool GetButtonDown(GamepadNumber _padNo, PhysicalInput _input) const = 0;

		virtual bool GetButtonUp(GamepadNumber _padNo, PhysicalInput _input) const = 0;

		virtual  void GetStickInput(GamepadNumber _padNo, GamepadStick _stick, Lib::Math::Vector2f* pOut) = 0;
	};
}
