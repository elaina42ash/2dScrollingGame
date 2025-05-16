#pragma once
#include "ChangeConditionMessage.h"

namespace ChangeBoolConditionMessageInternal
{
	struct ChangeBoolConditionMessageParams
	{
		PlayerStateComponent::PlayerConditionID conditionID;
		bool value;
	};
}


class ChangeBoolConditionMessage :public ChangeConditionMessage<ChangeBoolConditionMessageInternal::ChangeBoolConditionMessageParams>
{
public:
	explicit ChangeBoolConditionMessage(const ChangeBoolConditionMessageInternal::ChangeBoolConditionMessageParams& _params);

	TypeidSystem::TypeID GetTypeID() const override;
};
