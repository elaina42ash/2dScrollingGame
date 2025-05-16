#pragma once
#include "EntityState.h"

class IdleState : public EntityState
{
public:
	explicit IdleState(StatePattern::Entity* entity)
		: EntityState(entity)
	{
	}

	void Enter() override
	{
		EntityState::Enter();
	}
	void Update() override
	{
		EntityState::Update();
		bool shouldMove = true;
		if (shouldMove)  // 某种业务判断
		{
			entity_->RequestMove();  // 请求移动，由实体封装跳转细节
		}
	}
	void Exit() override
	{
		EntityState::Exit();
	}
};
