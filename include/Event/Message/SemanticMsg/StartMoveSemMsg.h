#pragma once
#include "Event/Message/IEventMessage.h"
#include "Lib/Math/TVector2.h"

class StartMoveSemMsg : public IEventMessage
{
private:
	Lib::Math::Vector2f moveInput_ ={0.0f,0.0f};

public:
	explicit StartMoveSemMsg(const Lib::Math::Vector2f& _moveInput);

	TypeidSystem::TypeID GetTypeID() const override;

	Lib::Math::Vector2f GetMoveInput() const;
};
