#pragma once
#include <map>

#include "StaticObjectPool.h"
#include "Fwk/Data/CSVData.h"
#include "GameObject/StaticObject.h"

class StaticObjectMng {
public:
	void Init();

	void Term();

	void Update();

	void Render();

	void GeneratePool(const char* _staticObjectName, int _poolSize);
	
	void DestroyPool(const char* _staticObjectName);

	void DestroyPoolAll();

	StaticObject* CreateStaticObject(const char* _staticObjectName, Lib::Math::Vector2f _position, ISceneContext* _sceneContext, ISceneGameplayAPI* _sceneGameplayAPI);

	void CreateStaticObjects(CSVData* _csvData, int _tileSize, ISceneContext* _sceneContext, ISceneGameplayAPI* _sceneGameplayAPI);

	int GetStaticObjectCount();

private:
	std::vector<StaticObject*> activeStaticObject_;

	std::map<std::string, StaticObjectPool> staticObjectPools_;
};
