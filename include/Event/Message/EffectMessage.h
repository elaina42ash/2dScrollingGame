#pragma once
#include "Message.h"
#include "component/PlayerStateComponent.h"

class EffectMessage :public Message
{
public:
	struct EffectMessageParams
	{
		PlayerStateComponent::PhysicsEffectType physicsEffectType_;
	};

private:
	EffectMessageParams params_;

public:

	EffectMessage( const EffectMessageParams& _params);

	const EffectMessageParams& GetParams()const;

	typeid_system::TypeID GetTypeID() const override;
};
