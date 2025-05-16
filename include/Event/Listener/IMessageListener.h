#pragma once
#include "Event/Message/IEventMessage.h"


class IMessageListener
	{
	public:
		virtual ~IMessageListener() = default;
		virtual void HandleMessage(const IEventMessage& _msg) = 0;
	};
