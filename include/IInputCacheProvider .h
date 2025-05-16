#pragma once
#include "Lib/Math/TVector2.h"

class IInputCacheProvider
{
public:
	virtual  ~IInputCacheProvider() = default;
	virtual Lib::Math::Vector2f GetInputCache() const =0;
};
