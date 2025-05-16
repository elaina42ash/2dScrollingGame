#pragma once
#include "IComponent.h"
#include "Inject.h"
#include "Timer/Timer.h"
#include "GameObject/GameObject.h"
class Component :virtual public IComponent
{
	friend GameObject;
private:
	Inject<IMessenger> messenger_;

	GameObject* owner_ = nullptr;

	int priority_ = 0;
	bool isActive_ = false;
	bool nextActive = isActive_;

protected:

	Timer timer_;

public:
	explicit Component(bool _isActive, IMessenger* _messenger);

	Component(IMessenger* _messenger);

	void Enable() override;

	void Disable() override;

	GameObject* GetOwner() const;

	void SetOwner(GameObject* _owner) override final;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	template<typename T>
	T* GetComponent();

	int GetPriority() const override final;

	void SetPriority(int _priority) override final;

	bool IsActive() const override final;

protected:
	virtual void Reset();

	void SendMsg(const IEventMessage& _message);

	IMessenger* GetMessengerPtr();

private:
	void SetActive(bool _isActive);

	void ApplyActiveChange();
};

template <typename T>
T* Component::GetComponent()
{
	return owner_ ? owner_->GetComponent<T>() : nullptr;
}
