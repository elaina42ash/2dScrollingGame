#pragma once
#include "Message.h"

class ChangeStateMessage :public Message
{
public:
	struct ChangeStateMessageParams
	{

	};

private:
	ChangeStateMessageParams params_;

public:

	ChangeStateMessage(const ChangeStateMessageParams& _params);

	const ChangeStateMessageParams& GetChangeStateParams()const;

	typeid_system::TypeID GetTypeID() const override;
};
