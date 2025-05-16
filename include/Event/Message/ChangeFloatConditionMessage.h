#pragma once
#include "ChangeConditionMessage.h"

namespace ChangeFloatConditionMessageInternal
{
	struct ChangeFloatConditionMessageParams
	{
		PlayerStateComponent::PlayerConditionID conditionID;
		float value;
	};
}

class ChangeFloatConditionMessage : public ChangeConditionMessage<ChangeFloatConditionMessageInternal::ChangeFloatConditionMessageParams>
{
public:
	explicit ChangeFloatConditionMessage(const ChangeFloatConditionMessageInternal::ChangeFloatConditionMessageParams& _params);

	TypeidSystem::TypeID GetTypeID() const override;
};
