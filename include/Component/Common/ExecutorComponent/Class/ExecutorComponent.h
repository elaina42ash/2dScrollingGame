#pragma once
#include <functional>
#include <queue>
#include "Component/Common/Component.h"

#pragma warning(push)
#pragma warning(disable:4250)
class  ExecutorComponent :public Component
{
private:
	std::queue<std::function<void()>> taskQueue_;

protected:
	explicit ExecutorComponent(bool _isActive,IMessenger* _messenger);

	ExecutorComponent(IMessenger* _messenger);

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	void AddTask(const std::function<void()>& _task);

	void Reset() override;

	bool TaskQueueIsEmpty() const;

	void ClearTaskQueue();
private:
	void ExecuteNextTask();


};
#pragma warning(pop)