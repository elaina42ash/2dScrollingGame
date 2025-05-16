#pragma once
#include "Event/Message/IEventMessage.h"
#include "Event/Listener/IMessageListener.h"
class IMessenger
{
public:
	virtual ~IMessenger() = default;

	virtual void SendMsg(const IEventMessage& _message) const = 0;

	virtual void Subscribe(size_t _msgType, IMessageListener* _listener) = 0;

	virtual void Unsubscribe(size_t _msgType, IMessageListener* _listener) = 0;

	virtual void Unsubscribe(IMessageListener* _listener) = 0;
};
