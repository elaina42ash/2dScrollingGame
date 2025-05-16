#pragma once
#include "Component/Common/Component.h"
#include "Event/Messenger.h"

class DecisionLogicalComponent : public Component
{
public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	DecisionLogicalComponent(bool _isActive, IMessenger* _messenger);

	explicit DecisionLogicalComponent(IMessenger* _messenger);

	void Reset() override;
};
