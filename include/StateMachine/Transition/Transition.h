#pragma once
#include <functional>
#include "StateMachine/Condition/AndCondition.h"



// 转移结构：定义从某状态到另一状态的切换规则
struct Transition
{
	int from_;			// 起始状态 ID
	int to_;			// 目标状态 ID
	AndCondition* condition_;		// 切换条件
	std::function<void()> action_;		// 切换动作（可捕获上下文）

	Transition(int _from, int _to, AndCondition* _condition, const std::function<void()>& _action);

	~Transition();

	Transition(const Transition& _other);

	Transition(Transition&& _other) noexcept;

	Transition& operator=(const Transition& _other);

	Transition& operator=(Transition&& _other) noexcept;
};
