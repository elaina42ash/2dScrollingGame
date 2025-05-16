#pragma once
#include "Listener/IMessageListener.h"

class IMessageBus
{
public:
	virtual ~IMessageBus() = default;

	virtual  void Unsubscribe(IMessageListener* _listener) =0 ;

	virtual void Unsubscribe(size_t _msgType, IMessageListener* _listener) = 0;

	virtual void Subscribe(size_t _msgType, IMessageListener* _listener) = 0;

	virtual void Publish(const IEventMessage& _message) = 0;
};
