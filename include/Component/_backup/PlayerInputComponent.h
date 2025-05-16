#pragma once
#include "Component.h"
#include "Event/Messenger.h"
#include "Lib/Math/TVector2.h"


class PlayerInputComponent : public Component
{
private:
	Messenger* messenger_;
public:
	explicit  PlayerInputComponent(Messenger* _messenger);

	PlayerInputComponent(bool _isActive, Messenger* _messenger);

	void Update() override;

private:
	Lib::Math::Vector2f GetMoveInput();

	bool MoveInputIsZero(const Lib::Math::Vector2f& _moveInput);
};


