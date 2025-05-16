#pragma once
#include "IMessenger.h"
#include "MessageBus.h"

class Messenger : public IMessenger
{
	using MsgType = size_t;

private:
	MessageBus* bus_ = nullptr;

public:
	explicit Messenger(MessageBus* _bus);

	void SendMsg(const IEventMessage& _message) const override;

	void Subscribe(MsgType _msgType, IMessageListener* _listener) override;

	void Unsubscribe(MsgType _msgType, IMessageListener* _listener) override;

	void Unsubscribe(IMessageListener* _listener) override;
};


