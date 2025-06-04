#pragma once
#include "Lib/Math/TVector2.h"

class ISceneGameplayAPI
{
public:
	virtual ~ISceneGameplayAPI() = default;

	virtual void CreateEnemy(const char* _enemyName, Lib::Math::Vector2f _position) = 0;

	virtual void CreateDroppedObject(const char* _objectName, Lib::Math::Vector2f _position) = 0;
};
