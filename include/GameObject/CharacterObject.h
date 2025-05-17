#pragma once
#include "GameObject.h"
#include "Inject.h"
#include "GameObjectMng/IEnvironmentQuery.h"

class CharacterObject : public GameObject
{
protected:
	Inject<IEnvironmentQuery> environmentQuery_;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Term() override;

	void InjectEnvironment(IEnvironmentQuery* _environmentQuery);
};


