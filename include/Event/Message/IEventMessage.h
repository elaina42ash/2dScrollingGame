#pragma once
#include "TypeID.h"


class IEventMessage : public TypeidSystem::ITypeID
{
public:
	virtual  ~IEventMessage() override = default;
};
