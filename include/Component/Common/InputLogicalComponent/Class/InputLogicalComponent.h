#pragma once
#include "Inject.h"
#include "Component/Common/Component.h"
#include "Event/IMessenger.h"

class InputLogicalComponent : public Component
{
public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	InputLogicalComponent(bool _isActive, IMessenger* _messenger);

	explicit InputLogicalComponent(IMessenger* _messenger);

	void Reset() override;
};
