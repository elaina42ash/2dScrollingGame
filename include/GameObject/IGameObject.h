#pragma once

class IGameObject
{
public:
	virtual  ~IGameObject() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Term() = 0;

	virtual void SetTag(const char* _tag) = 0;
	virtual const char* GetTag() const = 0;

	virtual bool GetActive() const = 0;

	virtual bool IsMarkedToDestroy() const = 0;
	virtual void MarkToDestroy() = 0;

	virtual void Enable() = 0;
	virtual void Disable() = 0;
};
