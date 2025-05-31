#pragma once
#include "Lib/Math/TVector2.h"

class IStaticObjectView
{
public:
	virtual  ~IStaticObjectView() = default;

	virtual  Lib::Math::Vector2f GetPosition() const = 0;
};
