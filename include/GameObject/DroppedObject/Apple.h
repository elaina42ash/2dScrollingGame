#pragma once
#include <memory>
#include "DroppedObject.h"

class Apple : public DroppedObject
{

public:
	Apple();

	~Apple() override;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

};
