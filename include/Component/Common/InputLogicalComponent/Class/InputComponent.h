#pragma once
#include "InputLogicalComponent.h"
#include "Component/Common/InputLogicalComponent/Interface/IInputComponent.h"
#include "Input/FrameworkPhysicsInputAdapter.h"
#include "Input/InputMapper.h"
#include "Input/LogicalInputAdapter.h"
#pragma warning(push)
#pragma warning(disable:4250)
class InputComponent : public InputLogicalComponent , public IInputComponent
{

private:
	FrameworkPhysicsInputAdapter physicsInputAdapter_;

protected:
	GameInput::InputMapper inputMapper_;

	GameInput::LogicalInputAdapter logicalInputAdapter_;

	Lib::Math::Vector2f moveInput_ = { 0.0f,0.0f };

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Term() override;

protected:
	InputComponent(bool _isActive, IMessenger* _messenger);

	explicit InputComponent(IMessenger* _messenger);

	void Reset() override;
};
#pragma warning(pop)