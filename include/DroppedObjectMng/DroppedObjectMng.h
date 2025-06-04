#pragma once
#include <map>

#include "DroppedObjectPool.h"
#include "Fwk/Data/CSVData.h"
#include "GameObject/StaticObject.h"

class DroppedObjectMng {
public:
	void Init();

	void Term();

	void Update();

	void Render();

	void GeneratePool(const char* _droppedObjectName, int _poolSize);

	void DestroyPool(const char* _droppedObjectName);

	void DestroyPoolAll();

	DroppedObject* CreateDroppedObject(const char* _droppedObjectName, Lib::Math::Vector2f _position, ISceneContext* _sceneContext, ISceneGameplayAPI* _sceneGameplayAPI);

	void CreateDroppedObjects(CSVData* _csvData, int _tileSize, ISceneContext* _sceneContext, ISceneGameplayAPI* _sceneGameplayAPI);

	int GetDroppedObjectCount();

private:
	std::vector<DroppedObject*> activeDroppedObject_;

	std::map<std::string, DroppedObjectPool> droppedObjectPools_;
};
