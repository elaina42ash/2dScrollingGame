#pragma once
#include "Inject.h"
#include "IState.h"
#include "Event/IMessenger.h"
#include "statemachine/IStateMachine.h"
#include "Timer/Timer.h"

class State : public IState
{
protected:
	Inject<IStateMachine> parent_;

	Inject<IMessenger> messenger_;

	Timer timer_;

	bool isExited_ =false;
public:
	explicit State(IStateMachine* _parent, IMessenger* _messenger);

	void Enter() override;
	void Update() override;
	void Exit() override;

	void SetParent(IStateMachine* _parent);

	const IStateMachine* GetParent() const;

	bool IsExited() const override final;

protected:
	void SendMsg(const IEventMessage& _message) const;
};
