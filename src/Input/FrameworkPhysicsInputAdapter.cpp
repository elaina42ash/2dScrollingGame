#include "Input/FrameworkPhysicsInputAdapter.h"

#include "Fwk/Framework.h"

bool FrameworkPhysicsInputAdapter::GetKey(GameInput::PhysicalInput _input) const
{
	switch (_input)
	{
	case GameInput::PhysicalInput::KEY_W:
		return Input_I->IsKeyPressed('W');
	case GameInput::PhysicalInput::KEY_S:
		return Input_I->IsKeyPressed('S');
	case GameInput::PhysicalInput::KEY_A:
		return Input_I->IsKeyPressed('A');
	case GameInput::PhysicalInput::KEY_D:
		return Input_I->IsKeyPressed('D');
	case GameInput::PhysicalInput::KEY_E:
		return Input_I->IsKeyPressed('E');
	case GameInput::PhysicalInput::KEY_J:
		return Input_I->IsKeyPressed('J');
	case GameInput::PhysicalInput::KEY_K:
		return Input_I->IsKeyPressed('K');
	case GameInput::PhysicalInput::KEY_L:
		return Input_I->IsKeyPressed('L');
	case GameInput::PhysicalInput::KEY_G:
		return Input_I->IsKeyPressed('G');
	case GameInput::PhysicalInput::KEY_UP:
		return Input_I->IsKeyPressed(VK_UP);
	case GameInput::PhysicalInput::KEY_DOWN:
		return Input_I->IsKeyPressed(VK_DOWN);
	case GameInput::PhysicalInput::KEY_LEFT:
		return Input_I->IsKeyPressed(VK_LEFT);
	case GameInput::PhysicalInput::KEY_RIGHT:
		return Input_I->IsKeyPressed(VK_RIGHT);
	case GameInput::PhysicalInput::KEY_SPACE:
		return Input_I->IsKeyPressed(VK_SPACE);
	default:
		return false;
	}
}

bool FrameworkPhysicsInputAdapter::GetKeyDown(GameInput::PhysicalInput _input) const
{
	switch (_input)
	{
	case GameInput::PhysicalInput::KEY_W:
		return Input_I->IsKeyDown('W');
	case GameInput::PhysicalInput::KEY_S:
		return Input_I->IsKeyDown('S');
	case GameInput::PhysicalInput::KEY_A:
		return Input_I->IsKeyDown('A');
	case GameInput::PhysicalInput::KEY_D:
		return Input_I->IsKeyDown('D');
	case GameInput::PhysicalInput::KEY_E:
		return Input_I->IsKeyDown('E');
	case GameInput::PhysicalInput::KEY_J:
		return Input_I->IsKeyDown('J');
	case GameInput::PhysicalInput::KEY_K:
		return Input_I->IsKeyDown('K');
	case GameInput::PhysicalInput::KEY_L:
		return Input_I->IsKeyDown('L');
	case GameInput::PhysicalInput::KEY_G:
		return Input_I->IsKeyDown('G');
	case GameInput::PhysicalInput::KEY_UP:
		return Input_I->IsKeyDown(VK_UP);
	case GameInput::PhysicalInput::KEY_DOWN:
		return Input_I->IsKeyDown(VK_DOWN);
	case GameInput::PhysicalInput::KEY_LEFT:
		return Input_I->IsKeyDown(VK_LEFT);
	case GameInput::PhysicalInput::KEY_RIGHT:
		return Input_I->IsKeyDown(VK_RIGHT);
	case GameInput::PhysicalInput::KEY_SPACE:
		return Input_I->IsKeyDown(VK_SPACE);
	default:
		return false;
	}
}

bool FrameworkPhysicsInputAdapter::GetKeyUp(GameInput::PhysicalInput _input) const
{
	switch (_input)
	{
	case GameInput::PhysicalInput::KEY_W:
		return Input_I->IsKeyUp('W');
	case GameInput::PhysicalInput::KEY_S:
		return Input_I->IsKeyUp('S');
	case GameInput::PhysicalInput::KEY_A:
		return Input_I->IsKeyUp('A');
	case GameInput::PhysicalInput::KEY_D:
		return Input_I->IsKeyUp('D');
	case GameInput::PhysicalInput::KEY_E:
		return Input_I->IsKeyUp('E');
	case GameInput::PhysicalInput::KEY_J:
		return Input_I->IsKeyUp('J');
	case GameInput::PhysicalInput::KEY_K:
		return Input_I->IsKeyUp('K');
	case GameInput::PhysicalInput::KEY_L:
		return Input_I->IsKeyUp('L');
	case GameInput::PhysicalInput::KEY_G:
		return Input_I->IsKeyUp('G');
	case GameInput::PhysicalInput::KEY_UP:
		return Input_I->IsKeyUp(VK_UP);
	case GameInput::PhysicalInput::KEY_DOWN:
		return Input_I->IsKeyUp(VK_DOWN);
	case GameInput::PhysicalInput::KEY_LEFT:
		return Input_I->IsKeyUp(VK_LEFT);
	case GameInput::PhysicalInput::KEY_RIGHT:
		return Input_I->IsKeyUp(VK_RIGHT);
	case GameInput::PhysicalInput::KEY_SPACE:
		return Input_I->IsKeyUp(VK_SPACE);
	default:
		return false;
	}
}

bool FrameworkPhysicsInputAdapter::GetButton(GameInput::GamepadNumber _padNo, GameInput::PhysicalInput _input) const
{
	int padNo = static_cast<int>(_padNo);

	switch (_input)
	{
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_B:
		return Input_I->IsButtonPressed(padNo, GAMEPAD_BUTTON::B);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_A:
		return Input_I->IsButtonPressed(padNo, GAMEPAD_BUTTON::A);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_X:
		return Input_I->IsButtonPressed(padNo, GAMEPAD_BUTTON::X);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_Y:
		return Input_I->IsButtonPressed(padNo, GAMEPAD_BUTTON::Y);
	default:
		return false;
	}
}

bool FrameworkPhysicsInputAdapter::GetButtonDown(GameInput::GamepadNumber _padNo, GameInput::PhysicalInput _input) const
{
	int padNo = static_cast<int>(_padNo);

	switch (_input)
	{
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_B:
		return Input_I->IsButtonDown(padNo, GAMEPAD_BUTTON::B);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_A:
		return Input_I->IsButtonDown(padNo, GAMEPAD_BUTTON::A);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_X:
		return Input_I->IsButtonDown(padNo, GAMEPAD_BUTTON::X);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_Y:
		return Input_I->IsButtonDown(padNo, GAMEPAD_BUTTON::Y);
	default:
		return false;
	}
}

bool FrameworkPhysicsInputAdapter::GetButtonUp(GameInput::GamepadNumber _padNo, GameInput::PhysicalInput _input) const
{
	int padNo = static_cast<int>(_padNo);

	switch (_input)
	{
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_B:
		return Input_I->IsButtonUp(padNo, GAMEPAD_BUTTON::B);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_A:
		return Input_I->IsButtonUp(padNo, GAMEPAD_BUTTON::A);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_X:
		return Input_I->IsButtonUp(padNo, GAMEPAD_BUTTON::X);
	case GameInput::PhysicalInput::GAMEPAD_BUTTON_Y:
		return Input_I->IsButtonUp(padNo, GAMEPAD_BUTTON::Y);
	default:
		return false;
	}
}

void FrameworkPhysicsInputAdapter::GetStickInput(GameInput::GamepadNumber _padNo, GameInput::GamepadStick _stick,
	Lib::Math::Vector2f* pOut)
{
	int padNo = static_cast<int>(_padNo);
	GAMEPAD_STICK stick = static_cast<GAMEPAD_STICK>(_stick);
	Input_I->GetStickInput(padNo, stick, pOut);
}
