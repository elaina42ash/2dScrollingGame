#include "Event/Messenger.h"


Messenger::Messenger(MessageBus* _bus): bus_(_bus)
{
}

void Messenger::SendMsg(const IEventMessage& _msg) const
{
	if (!bus_)
		return;

	bus_->Publish(_msg);
}

void Messenger::Subscribe(MsgType _msgType, IMessageListener* _listener)
{
	if (!bus_)
		return;
	bus_->Subscribe(_msgType, _listener);
}

void Messenger::Unsubscribe(MsgType _msgType, IMessageListener* _listener)
{
	if (!bus_)
		return;
	bus_->Unsubscribe(_msgType, _listener);
}

void Messenger::Unsubscribe(IMessageListener* _listener)
{
	if (!bus_)
		return;
	bus_->Unsubscribe( _listener);
}
