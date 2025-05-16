#pragma once

#include "Entity.h"
#include "State.h"

class EntityState : public State
{
public:
	void Enter() override
	{
		State::Enter();
	}
	void Update() override
	{
		State::Update();
	}
	void Exit() override
	{
		State::Exit();
	}

protected:
	StatePattern::Entity* entity_;
public:
	EntityState(IStateMachine* _parent, StatePattern::Entity* _entity)
		: State(_parent),
		  entity_(_entity)
	{
	}
};
