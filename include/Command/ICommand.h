#pragma once
#include "TypeID.h"


class ICommand : public TypeidSystem::ITypeID
{
public:
	enum class CommandType
	{
		NONE = -1,
		START_MOVE = 1000,
		START_JUMP,
		RELEASE_JUMP,
		START_GRAVITY,
		START_FRICTION
	};

public:
	virtual const CommandType& GetCmdType() = 0;
	virtual ~ICommand() = default;
};
