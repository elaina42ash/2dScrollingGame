#pragma once
#include "Command.h"
#include "Lib/Math/TVector2.h"

class StartMoveIntentCommand : public Command
{
public:
	Lib::Math::Vector2f moveInput_;

	StartMoveIntentCommand(const Lib::Math::Vector2f& _moveInput);

	const Lib::Math::Vector2f& GetMoveInput() const;

	TypeidSystem::TypeID GetTypeID() const override;
};
