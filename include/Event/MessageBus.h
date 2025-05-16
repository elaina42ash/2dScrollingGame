#pragma once
#include <unordered_map>
#include "IMessageBus.h"
#include "Listener/IMessageListener.h"
#include "Message/IEventMessage.h"

class MessageBus : public IMessageBus
{
	using MsgType = size_t;

	friend class Messenger;
private:
	std::unordered_map<MsgType, std::vector<IMessageListener*>> messageTypeToListeners_;

public:
	MessageBus() = default;

private:
	void Unsubscribe(IMessageListener* _listener) override;

	void Unsubscribe(MsgType _msgType, IMessageListener* _listener) override;

	void Subscribe(MsgType _msgType, IMessageListener* _listener) override;

	void Publish(const IEventMessage& _message) override;
};
