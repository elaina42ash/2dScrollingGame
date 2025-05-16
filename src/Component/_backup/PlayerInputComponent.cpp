#include "component/PlayerInputComponent.h"

#include <iostream>

#include "GameMath.h"
#include "Command/ReleaseJumpIntentCommand.h"
#include "command/StartJumpIntentCommand.h"
#include "command/StartMoveIntentCommand.h"
#include "Event/Message/InputMessage.h"
#include "Fwk/Framework.h"

PlayerInputComponent::PlayerInputComponent(Messenger* _messenger):messenger_(_messenger)
{}

PlayerInputComponent::PlayerInputComponent(bool _isActive, Messenger* _messenger): Component(_isActive),
	messenger_(_messenger)
{
}

void PlayerInputComponent::Update()
{
	Lib::Math::Vector2f moveInput = GetMoveInput();

	if (!MoveInputIsZero(moveInput))
	{
		StartMoveIntentCommand startMoveCommand(moveInput);
		InputMessage startMoveMsg(&startMoveCommand);
		if (!messenger_)
			return;
		messenger_->SendMSG(startMoveMsg);
	}

	if (Input_I->IsButtonUp(0, GAMEPAD_BUTTON::B) || Input_I->IsKeyUp(VK_SPACE))
	{
		ReleaseJumpIntentCommand releaseJumpIntentCommand;
		InputMessage releaseJumpMsg(&releaseJumpIntentCommand);
		if (!messenger_)
			return;
		messenger_->SendMSG(releaseJumpMsg);
	}

	if ((Input_I->IsButtonDown(0, GAMEPAD_BUTTON::B) || Input_I->IsKeyDown(VK_SPACE)) )
	{
		StartJumpIntentCommand startJumpCommand;
		InputMessage startJumpMsg(&startJumpCommand);
		if (!messenger_)
		return;
		messenger_->SendMSG(startJumpMsg);
	}
}

Lib::Math::Vector2f PlayerInputComponent::GetMoveInput()
{
	// ゲームパッドの入力を取得
	Lib::Math::Vector2f vInput = { 0.0f,0.0f };

	// controller
	Input_I->GetStickInput(0, GAMEPAD_STICK::LEFT, &vInput);

	// keyboard
	if (Input_I->IsKeyPressed(VK_LEFT))
	{
		vInput.x = -2.0f;
	}
	if (Input_I->IsKeyPressed(VK_RIGHT))
	{
		vInput.x = 2.0f;
	}
	if (Input_I->IsKeyPressed(VK_UP))
	{
		vInput.y = 2.0f;
	}
	if (Input_I->IsKeyPressed(VK_DOWN))
	{
		vInput.y = -2.0f;
	}

	// Y成分を取り除く
	vInput.y = 0.0f;

	return vInput;
}

bool PlayerInputComponent::MoveInputIsZero(const Lib::Math::Vector2f& _moveInput)
{
	if (GameMath::FloatIsZero(_moveInput.x) && GameMath::FloatIsZero(_moveInput.y))
		return true;
	return false;
}

