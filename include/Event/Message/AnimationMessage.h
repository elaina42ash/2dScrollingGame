#pragma once
#include "Message.h"
#include "Component/PlayerAnimationComponent.h"

class AnimationMessage :public Message
{
public:
	struct AnimationMessageParams
	{
		AnimationID animationID_;
		AnimationPlayStyle animationPlayStyle;
	};

private:
	AnimationMessageParams params_;

public:
	AnimationMessage(const AnimationMessageParams& _params);

	const AnimationMessageParams& GetParams()const
		;

	typeid_system::TypeID GetTypeID() const override;
};