#pragma once
#include <Inject.h>
#include "ILogicalInputAdapter.h"
#include "IPhysicsInputAdapter.h"

namespace GameInput
{
	class LogicalInputAdapter : public ILogicalInputAdapter
	{
	private:
		Inject<IPhysicsInputAdapter> physicsInputAdapter_;
		Inject<IInputMapper> inputMapper_;

	public:
		LogicalInputAdapter(IPhysicsInputAdapter* _physicsInputAdapter,
			IInputMapper* _inputMapper);

	public:

		bool GetKey(GameInput::LogicalInput _input) const override;

		bool GetKeyDown(LogicalInput _input) const override;

		bool GetKeyUp(LogicalInput _input) const override;

		bool GetButton(GamepadNumber _padNo, LogicalInput _input) const override;

		bool GetButtonDown(GamepadNumber _padNo, LogicalInput _input) const override;

		bool GetButtonUp(GamepadNumber _padNo, LogicalInput _input) const override;

		void GetStickInput(GamepadNumber _padNo, GamepadStick _stick, Lib::Math::Vector2f* pOut)  const override;

		float GetAxis(Axis _axis) const override;

		float GetAxisRaw(Axis _axis) const override;
	};

	inline LogicalInputAdapter::LogicalInputAdapter(IPhysicsInputAdapter* _physicsInputAdapter,
		IInputMapper* _inputMapper):physicsInputAdapter_(_physicsInputAdapter), inputMapper_(_inputMapper)
	{
	}

	inline bool LogicalInputAdapter::GetKey(GameInput::LogicalInput _input) const
	{
		if (!physicsInputAdapter_ || !inputMapper_)
			return false;
		return physicsInputAdapter_->GetKey(inputMapper_->GetMappedPhysicalInput(_input));
	}

	inline bool LogicalInputAdapter::GetKeyDown(LogicalInput _input) const
	{
		if (!physicsInputAdapter_ || !inputMapper_)
			return false;
		return physicsInputAdapter_->GetKeyDown(inputMapper_->GetMappedPhysicalInput(_input));
	}

	inline bool LogicalInputAdapter::GetKeyUp(LogicalInput _input) const
	{
		if (!physicsInputAdapter_ || !inputMapper_)
			return false;
		return physicsInputAdapter_->GetKeyUp(inputMapper_->GetMappedPhysicalInput(_input));
	}

	inline bool LogicalInputAdapter::GetButton(GamepadNumber _padNo, LogicalInput _input) const
	{
		if (!physicsInputAdapter_ || !inputMapper_)
			return false;
		return physicsInputAdapter_->GetButton(_padNo, inputMapper_->GetMappedPhysicalInput(_input));
	}

	inline bool LogicalInputAdapter::GetButtonDown(GamepadNumber _padNo, LogicalInput _input) const
	{
		if (!physicsInputAdapter_ || !inputMapper_)
			return false;
		return physicsInputAdapter_->GetButtonDown(_padNo, inputMapper_->GetMappedPhysicalInput(_input));
	}

	inline bool LogicalInputAdapter::GetButtonUp(GamepadNumber _padNo, LogicalInput _input) const
	{
		if (!physicsInputAdapter_ || !inputMapper_)
			return false;
		return physicsInputAdapter_->GetButtonUp(_padNo, inputMapper_->GetMappedPhysicalInput(_input));
	}

	inline void LogicalInputAdapter::GetStickInput(GamepadNumber _padNo, GamepadStick _stick, Lib::Math::Vector2f* pOut) const
	{
		if (!physicsInputAdapter_)
			return;
		physicsInputAdapter_->GetStickInput(_padNo, _stick, pOut);
	}

	inline float LogicalInputAdapter::GetAxis(Axis _axis) const
	{
		// TODO:Only one player is supported for now
		Lib::Math::Vector2f vInput = { 0.0f,0.0f };

		GetStickInput(GamepadNumber::GAMEPAD_NUMBER_1, GamepadStick::LEFT, &vInput);

		if (GetKey(LogicalInput::MOVE_LEFT))
		{
			vInput.x = -1.0f;
		}

		if (GetKey(LogicalInput::MOVE_RIGHT))
		{
			vInput.x = 1.0f;
		}

		if (GetKey(LogicalInput::MOVE_UP))
		{
			vInput.y = 1.0f;
		}

		if (GetKey(LogicalInput::MOVE_DOWN))
		{
			vInput.y = -1.0f;
		}

		switch (_axis)
		{
		case Axis::VERTICAL:
			return vInput.y;
		case Axis::HORIZONTAL:
			return vInput.x;
		default:
			return 0.0f;
		}
	}

	inline float LogicalInputAdapter::GetAxisRaw(Axis _axis) const
	{
		float value = GetAxis(_axis);

		if (value < -1.0f)
			value = -1.0f;
		else if (value > 1.0f)
			value = 1.0f;

		return value;
	}
}

