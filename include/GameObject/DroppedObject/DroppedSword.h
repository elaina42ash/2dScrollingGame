#pragma once
#include <memory>

#include "DroppedObject.h"
#include "GameObject/Equipment/Weapon/Sword.h"

class DroppedSword : public DroppedObject
{
private:
	std::shared_ptr<Sword> sword_;
public:
	DroppedSword();

	~DroppedSword() override;



	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;


};
