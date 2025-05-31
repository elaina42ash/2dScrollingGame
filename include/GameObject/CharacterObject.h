#pragma once
#include "GameObject.h"
#include "Inject.h"

class CharacterObject : public GameObject
{
public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Term() override;
};


