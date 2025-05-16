#include "Component/Common/ExecutorComponent/Class/ExecutorComponent.h"
#include "Component/Common/Component.h"

ExecutorComponent::ExecutorComponent(bool _isActive, IMessenger* _messenger) :Component(_isActive, _messenger)
{
}

ExecutorComponent::ExecutorComponent(IMessenger* _messenger):Component(_messenger)
{
		
}

void ExecutorComponent::Init()
{
	Component::Init();
}

void ExecutorComponent::Render()
{
	Component::Render();
}

void ExecutorComponent::Term()
{
	Component::Term();
}

void ExecutorComponent::Update()
{
	Component::Update();
	while (!taskQueue_.empty())
	{
		ExecuteNextTask();
	}
}

void ExecutorComponent::AddTask(const std::function<void()>& _task)
{
	taskQueue_.push(_task);
}

void ExecutorComponent::Reset()
{
	Component::Reset();
	ClearTaskQueue();
}

void ExecutorComponent::ExecuteNextTask()
{
	auto& task = taskQueue_.front();
	try
	{
		task();
	}
	catch (const std::exception& e)
	{

	}
	taskQueue_.pop();
}

bool ExecutorComponent::TaskQueueIsEmpty() const
{
	return taskQueue_.empty();
}

void ExecutorComponent::ClearTaskQueue()
{
	while (!TaskQueueIsEmpty())
		taskQueue_.pop();
}
