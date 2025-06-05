#include "Component/Player/InputLogicalComponent/Class/PlayerInputComponent.h"
#include "GameMath.h"
#include "Component/Common/InputLogicalComponent/Class/InputComponent.h"
#include "Event/IMessenger.h"
#include "Event/Message/LogicalInputMsg/AttackInputMsg.h"
#include "Event/Message/LogicalInputMsg/DashInputMsg.h"
#include "Event/Message/LogicalInputMsg/DropWeaponInput.h"
#include "Event/Message/LogicalInputMsg/HoriAxisInputMsg.h"
#include "Event/Message/LogicalInputMsg/InteractInputMsg.h"
#include "Event/Message/LogicalInputMsg/JumpInputMsg.h"
#include "Event/Message/LogicalInputMsg/ReleaseJumpInputMsg.h"
#include "Event/Message/LogicalInputMsg/SwitchWeaponInputMsg.h"

PlayerInputComponent::PlayerInputComponent(bool _isActive, IMessenger* _messenger) : ::InputComponent(_isActive, _messenger)
{
}

PlayerInputComponent::PlayerInputComponent(IMessenger* _messenger) : InputComponent(_messenger)
{
}

void PlayerInputComponent::Init()
{
	InputComponent::Init();
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_W, GameInput::LogicalInput::MOVE_UP);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_S, GameInput::LogicalInput::MOVE_DOWN);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_A, GameInput::LogicalInput::MOVE_LEFT);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_D, GameInput::LogicalInput::MOVE_RIGHT);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_E, GameInput::LogicalInput::SWITCH_WEAPON);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_J, GameInput::LogicalInput::ATTACK);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_L, GameInput::LogicalInput::DASH);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_K, GameInput::LogicalInput::INTERACT);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_G, GameInput::LogicalInput::DROP_WEAPON);
	inputMapper_.BindPhysicalToLogical(GameInput::PhysicalInput::KEY_SPACE, GameInput::LogicalInput::JUMP);
}

void PlayerInputComponent::Update()
{
	InputComponent::Update();
	Lib::Math::Vector2f dirInput = { 0.0f,0.0f };
	dirInput.x = logicalInputAdapter_.GetAxis(GameInput::Axis::HORIZONTAL);

	// Horizontal axis input detected
	if (!GameMath::FloatIsZero(dirInput.x))
	{
		HoriAxisInputMsg HorizontalAxisMsg(dirInput.x);
		SendMsg(HorizontalAxisMsg);
	}

	// jump input detected
	if (logicalInputAdapter_.GetKeyDown(GameInput::LogicalInput::JUMP) || logicalInputAdapter_.GetButtonDown(GameInput::GamepadNumber::GAMEPAD_NUMBER_1, GameInput::LogicalInput::JUMP))
	{
		JumpInputMsg jumpInputMsg;
		SendMsg(jumpInputMsg);
	}

	// release jump input detected
	if (logicalInputAdapter_.GetKeyUp(GameInput::LogicalInput::JUMP) || logicalInputAdapter_.GetButtonUp(GameInput::GamepadNumber::GAMEPAD_NUMBER_1, GameInput::LogicalInput::JUMP))
	{
		ReleaseJumpInputMsg releaseJumpInputMsg;
		SendMsg(releaseJumpInputMsg);
	}

	// start attack input detected
	if (logicalInputAdapter_.GetKeyDown(GameInput::LogicalInput::ATTACK) || logicalInputAdapter_.GetButtonUp(GameInput::GamepadNumber::GAMEPAD_NUMBER_1, GameInput::LogicalInput::ATTACK))
	{
		AttackInputMsg attackInputMsg;
		SendMsg(attackInputMsg);
	}

	// start dash input detected
	if (logicalInputAdapter_.GetKeyDown(GameInput::LogicalInput::DASH))
	{
		DashInputMsg dashInputMsg;
		SendMsg(dashInputMsg);
	}

	// start dash input detected
	if (logicalInputAdapter_.GetKeyDown(GameInput::LogicalInput::SWITCH_WEAPON))
	{
		SwitchWeaponInputMsg switchWeaponInput;
		SendMsg(switchWeaponInput);
	}

	if (logicalInputAdapter_.GetKeyDown(GameInput::LogicalInput::INTERACT))
	{
		InteractInputMsg interactInputMsg;
		SendMsg(interactInputMsg);
	}


	if (logicalInputAdapter_.GetKeyDown(GameInput::LogicalInput::DROP_WEAPON))
	{
		DropWeaponInput dropWeaponInput;
		SendMsg(dropWeaponInput);
	}
	Reset();
}

void PlayerInputComponent::Render()
{
	InputComponent::Render();
}

void PlayerInputComponent::Term()
{
	InputComponent::Term();
}

void PlayerInputComponent::Reset()
{
	InputComponent::Reset();
}
