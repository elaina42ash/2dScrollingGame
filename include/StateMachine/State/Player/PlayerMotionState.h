#pragma once
#include "StateMachine/InnerStateMachine.h"

class PlayerMotionState : public InnerStateMachine
{
public:
	PlayerMotionState(IStateMachine* _parent, IMessenger* _messenger);

	void Enter() override;

	void Update() override;

	void Exit() override;

	IStateMachine* AsStateMachine() override;
};
