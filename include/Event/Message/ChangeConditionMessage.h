#pragma once
#include "Message.h"
#include "Component/PlayerStateComponent.h"

template <typename T>
class ChangeConditionMessage :public Message
{
private:
	T params_;

public:
	ChangeConditionMessage(const T& _params);

	const T& GetParams()const;

	TypeidSystem::TypeID GetTypeID() const override = 0;
};

template <typename T>
ChangeConditionMessage<T>::ChangeConditionMessage(const T& _params):Message(MessageType::CHANGE_CONDITION),params_(_params)
{
		
}

template <typename T>
const T& ChangeConditionMessage<T>::GetParams() const
{
	return params_;
}