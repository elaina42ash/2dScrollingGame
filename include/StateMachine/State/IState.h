#pragma once

class IStateMachine;
class IState
{
public:
	virtual ~IState() = default;

	virtual void Enter() = 0;

	virtual void Update() = 0;

	virtual void Exit() = 0;

	virtual bool IsExited() const = 0;

	virtual IStateMachine* AsStateMachine() = 0;

};
