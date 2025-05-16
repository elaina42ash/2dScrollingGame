#pragma once

class IGameObject
{
public:
	virtual  ~IGameObject() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Term() = 0;

};
