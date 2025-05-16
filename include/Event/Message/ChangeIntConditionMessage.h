#pragma once
#include "ChangeConditionMessage.h"

namespace ChangeIntConditionMessageInternal
{
	struct ChangeIntConditionMessageParams
	{
		PlayerStateComponent::PlayerConditionID conditionID;
		int value;
	};
}
class ChangeIntConditionMessage: public ChangeConditionMessage<ChangeIntConditionMessageInternal::ChangeIntConditionMessageParams>
{
public:
	explicit ChangeIntConditionMessage(const ChangeIntConditionMessageInternal::ChangeIntConditionMessageParams& _params);

	TypeidSystem::TypeID GetTypeID() const override;
};
