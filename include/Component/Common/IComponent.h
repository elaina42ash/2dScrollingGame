#pragma once
class GameObject;
class IComponent
{
public:
	virtual  ~IComponent() = default;

	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual void Render() = 0;

	virtual void Term() = 0;

	virtual void Enable() = 0;

	virtual void Disable() = 0;

	virtual void SetOwner(GameObject* _owner) = 0;

	virtual int GetPriority() const = 0;

	virtual void SetPriority(int _priority) = 0;

	virtual bool IsActive() const =0;
};
