#pragma once
#include "Component/Common/InputLogicalComponent/Class/InputComponent.h"

#pragma warning(push)
#pragma warning(disable:4250)
class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent(bool _isActive, IMessenger* _messenger);

	explicit PlayerInputComponent(IMessenger* _messenger);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

protected:
	void Reset() override;
};
#pragma warning(pop)