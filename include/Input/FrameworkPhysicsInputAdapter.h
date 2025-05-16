#pragma once
#include "IPhysicsInputAdapter.h"
#include "Lib/Math/TVector2.h"

class FrameworkPhysicsInputAdapter : public  GameInput::IPhysicsInputAdapter
{
public:

	bool GetKey(GameInput::PhysicalInput _input) const override;

	bool GetKeyDown(GameInput::PhysicalInput _input) const override;

	bool GetKeyUp(GameInput::PhysicalInput _input) const override;

	bool GetButton(GameInput::GamepadNumber _padNo, GameInput::PhysicalInput _input) const override;

	bool GetButtonDown(GameInput::GamepadNumber _padNo, GameInput::PhysicalInput _input) const override;

	bool GetButtonUp(GameInput::GamepadNumber _padNo, GameInput::PhysicalInput _input) const override;

	void GetStickInput(GameInput::GamepadNumber _padNo, GameInput::GamepadStick _stick,
		Lib::Math::Vector2f* pOut) override;
};
