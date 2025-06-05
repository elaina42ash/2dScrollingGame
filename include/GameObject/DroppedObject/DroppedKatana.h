#pragma once
#include <memory>

#include "DroppedObject.h"
#include "GameObject/Equipment/Weapon/Katana.h"

class DroppedKatana : public DroppedObject
{
private:
	std::shared_ptr<Katana> Katana_;
public:
	DroppedKatana();

	~DroppedKatana() override;

	std::shared_ptr<Katana> GetKatana() const;

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	void HandleMessage(const IEventMessage& _msg) override;

};
