#include "Event/MessageBus.h"

void MessageBus::Unsubscribe(IMessageListener* _listener)
{
	for (auto& pair : messageTypeToListeners_)
	{
		auto& vec = pair.second;
		vec.erase(std::remove(vec.begin(), vec.end(), _listener), vec.end());
	}
}

void MessageBus::Unsubscribe(MsgType _msgType, IMessageListener* _listener)
{
	auto it = messageTypeToListeners_.find(_msgType);
	if (it != messageTypeToListeners_.end())
	{
		auto& vec = it->second;
		vec.erase(std::remove(vec.begin(), vec.end(), _listener), vec.end());
	}
}

void MessageBus::Subscribe(MsgType _msgType, IMessageListener* _listener)
{
	auto& vec = messageTypeToListeners_[_msgType];
	if (std::find(vec.begin(), vec.end(), _listener) == vec.end())
	{
		vec.push_back(_listener);
	}
}

void MessageBus::Publish(const IEventMessage& _message)
{
	MsgType id = _message.GetTypeID();
	auto it = messageTypeToListeners_.find(id);
	if (it == messageTypeToListeners_.end())
		return;

	for (auto* listener : it->second)
	{
		if (listener)
		{
			listener->HandleMessage(_message);
		}
	}
}
