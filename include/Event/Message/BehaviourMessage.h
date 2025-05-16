#pragma once
#include "Message.h"
#include "component/PlayerStateComponent.h"
#include "Lib/Math/TVector2.h"


class BehaviourMessage:public Message
{
public:
	struct BehaviourMessageParams
	{
		PlayerStateComponent::BehaviourType behaviourType_;
		Lib::Math::Vector2f moveInput;
	};

private:
	BehaviourMessageParams params_;

public:
	BehaviourMessage(const BehaviourMessageParams& _params);

	const BehaviourMessageParams& GetMoveParams()const
		;

	typeid_system::TypeID GetTypeID() const override;
};
